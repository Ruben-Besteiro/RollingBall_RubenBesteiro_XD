// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPlayerController.h"
#include "Ball.h"
#include "CanvasItem.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

ABallPlayerController::ABallPlayerController()
{
	Counter = 0;
}


void ABallPlayerController::OnLoseLife()
{
	CurrentLives--;
	UpdateUILives(CurrentLives);

	APawn* P = GetPawn();

	// Reseteamos los rings
	TArray<AActor*> Coins;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Coin", Coins);

	for (AGoldCube* Coin : CollectedCoins)
	{
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
		CurrentScore = SavedScore;
		UpdateUIScore(CurrentScore);

		UnPossess();
		P->Destroy();
		GetWorld()->GetAuthGameMode()->RestartPlayer(this);
	} else
	{
		GameOver();
	}
}


void ABallPlayerController::OnCollectCoin(AGoldCube* Coin)
{
	CollectedCoins.Add(Coin);
	CurrentScore += 1;
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
	if (CurrentLives > 0) MusicComponent->Play();		// En game over es mejor que se calle
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
		if (CurrentTime > -1)
		{
			UpdateUITime(CurrentTime);
		} else
		{
			CurrentLives = 0;			// Si nos quedamos sin tiempo es GG
			OnLoseLife();
		}
	}
}

void ABallPlayerController::GameOver()
{
	bShowMouseCursor = true;
	MusicComponent->Stop();
	UGameplayStatics::PlaySound2D(this, GameOverSound);

	//mostrar widget de gameover
	auto WidgetCreated = CreateWidget(this, GameOverWidgetClass);
	WidgetCreated->AddToViewport();
}