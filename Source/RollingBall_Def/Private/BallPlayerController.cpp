// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPlayerController.h"
#include "Ball.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"
#include "GameFramework/PlayerStart.h"

ABallPlayerController::ABallPlayerController()
{
	Counter = 0;
}


void ABallPlayerController::OnLoseLife()
{
	if (!isGG)
	{
		CurrentLives--;
		UpdateUILives(CurrentLives);
	}

	APawn* P = GetPawn();

	// Reseteamos los rings y los powerups
	
	TArray<AActor*> Coins;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Coin", Coins);
	for (AGoldCube* Coin : CollectedCoins)
	{
		// Las monedas guardadas no vuelven al morir porque si lo hiciesen nos podríamos saltar el objetivo del juego
		// de conseguir todas las monedas (porque podríamos pillar algunas 2 veces)
		if (!CollectedSavedCoins.Contains(Coin))
		{
			Coin->SetActorHiddenInGame(false);
			Coin->SetActorEnableCollision(true);
			Coin->SetActorTickEnabled(true);
		}
	}

	if (CurrentLives > 0)
	{
		if (CurrentScore != SavedScore) UGameplayStatics::PlaySound2D(GetWorld(), LoseMoneySound);
		
		// Restauramos el score del último checkpoint antes de reiniciar
		int LostMoney = CurrentScore - SavedScore;
		CurrentScore = SavedScore;
		UpdateUIScore(CurrentScore);

		TArray<AActor*> PowerUps;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "PowerUp", PowerUps);
		for (AActor* PowerUp : PowerUps)
		{
			PowerUp->SetActorHiddenInGame(false);
			PowerUp->SetActorEnableCollision(true);
			PowerUp->SetActorTickEnabled(true);
		}

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Dust, P->GetActorLocation());
		UnPossess();
		P->Destroy();
		GetWorld()->GetAuthGameMode()->RestartPlayer(this);

		/*// Código de soltar las monedas
		TArray<AGoldCube*>CollectedNonSavedCoins;
		for (int i = 0; i < LostMoney; i++)
		{
			CollectedNonSavedCoins.AddUnique(CollectedCoins[i]);
		}
		UE_LOG(LogTemp, Warning, TEXT("Has perdido %d monedas"), CollectedNonSavedCoins.Num());
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = nullptr;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStarts[0]);

		for (int i = 0; i < LostMoney; i++)
		{
			// Spawneamos las monedas que perdimos pero sin hitbox (PhysicsOnly)
			AActor* NewActor = GetWorld()->SpawnActor<AActor>(E, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParams);
			TArray<UPrimitiveComponent*> PrimComps;
			NewActor->GetComponents<UPrimitiveComponent>(PrimComps);
			for (UPrimitiveComponent* Comp : PrimComps)
			{
				Comp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				Comp->SetSimulatePhysics(true);
				FVector Impulse = FVector(FMath::FRandRange(-1.f,1.f), FMath::FRandRange(-1.f,1.f), 0.5f) * 100000.f;
				Comp->AddImpulse(Impulse, NAME_None, true);
			}

			// Después de medio segundo activamos su hitbox
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [NewActor]()
			{
				if (!NewActor) return;

				TArray<UPrimitiveComponent*> PrimComps;
				NewActor->GetComponents<UPrimitiveComponent>(PrimComps);

				for (UPrimitiveComponent* Comp : PrimComps)
				{
					Comp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
					Comp->SetCollisionProfileName(TEXT("OverlapAll"));
				}
			}, 0.5f, false);
		}*/

	} else
	{
		GameOver();
	}
}


void ABallPlayerController::OnCollectCoin(AGoldCube* Coin)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCollectCoin"));
	CollectedCoins.Add(Coin);			// CurrentScore es equivalente al tamaño del array de monedas coleccionadas
	CurrentScore += 1;					// Y lo mismo con SavedScore y el array de monedas guardadas (cuando tocamos un checkpoint)
	UpdateUIScore(CurrentScore);
}

void ABallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get the local player subsystem to add input mapping context
	auto Input = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Input->AddMappingContext(ControlsMaps, 0);

	//UGameplayStatics::PlaySound2D(GetWorld(), Music);
	MusicComponent = NewObject<UAudioComponent>(this);
	MusicComponent->bAutoActivate = false;
	MusicComponent->SetSound(Music);
	MusicComponent->SetVolumeMultiplier(0.3f);		// Esto es para que los SFX se oigan
	MusicComponent->RegisterComponent();

	// Esto es para reiniciar la música cuando se termine
	MusicComponent->OnAudioFinished.AddDynamic(this, &ABallPlayerController::OnMusicFinished);
	
	MusicComponent->Play();
}

void ABallPlayerController::OnMusicFinished()
{
	if (CurrentLives > 0 && !isGG) MusicComponent->Play();		// En game over es mejor que se calle
}

void ABallPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABall* BallPawn = Cast<ABall>(InPawn);
	// Yo (controlador) le digo a la bola que yo soy su controlador
	BallPawn->SetBallController(this);
}

void ABallPlayerController::Tick(float DeltaTime)
{
	Counter += DeltaTime;
	
	if ((int)Counter != (int)(Counter - DeltaTime))		// Esto solo será true si no hay ningún decimal
	{
		CurrentTime--;
		if (CurrentTime >= 0 && !isGG)
		{
			UpdateUITime(CurrentTime);
		} else if (CurrentTime < 0 && !isGG)
		{
			CurrentLives = 0;			// Si nos quedamos sin tiempo es muerte
			OnLoseLife();
		} if (isGG)
		{
			GG();		// Cambia el texto a amarillo y hace invisible al jugador
		}
	}
}

void ABallPlayerController::GameOver()
{
	if (!isGG)
	{
		bShowMouseCursor = true;
		MusicComponent->DestroyComponent();
		UGameplayStatics::PlaySound2D(this, GameOverSound);

		//mostrar widget de gameover
		auto WidgetCreated = CreateWidget(this, GameOverWidgetClass);
		WidgetCreated->AddToViewport();
	}
}