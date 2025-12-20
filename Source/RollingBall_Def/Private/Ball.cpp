// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "BallPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Mecanisms/GoldCube.h"

// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 

	// Componentes del actor
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));

	// Jerarquia de componentes
	RootComponent = MyMesh;
	MySpringArm->SetupAttachment(MyMesh);
	MyCamera->SetupAttachment(MySpringArm);
}

void ABall::SetBallController(ABallPlayerController* BallPlayerController)
{
	this->BallController = BallPlayerController;
}

// Como el start de unity
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	// Config de físicas y peso
    MyMesh->SetSimulatePhysics(true);
    MyMesh->SetEnableGravity(true);
    MyMesh->SetMassOverrideInKg(NAME_None, 100);
	
	OnTakeAnyDamage.AddDynamic(this, &ABall::DamageTaken);
	UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAAAAAAAAA"));
	MoveForceInicial = MoveForce;
	UE_LOG(LogTemp, Warning, TEXT("%f"), MoveForceInicial);
}

void ABall::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsInvincible) return;
	
	if(BallController && DeathSound)
	{
		//UGameplayStatics::PlaySound2D(GetWorld(), DeathSound, 1);		El sonido de muerte lo reproduzco por blueprints para arreglar un bug de Unreal
		BallController->OnLoseLife();
	}
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->ActorHasTag("Coin"))
	{
		BallController->OnCollectCoin(Cast<AGoldCube>(OtherActor));
		UGameplayStatics::PlaySound2D(this, RingSound);

		OtherActor->SetActorHiddenInGame(true);
		OtherActor->SetActorEnableCollision(false);
		OtherActor->SetActorTickEnabled(false);
	}
	else if (OtherActor->ActorHasTag("DeathZone"))
	{
		BallController->OnLoseLife();
	}
}

void ABall::Move(const FInputActionValue& InputActionValue)
{
	const auto InputVector = InputActionValue.Get<FVector2D>();

	MyMesh->AddForce(FVector(InputVector.Y, InputVector.X, 0) * MoveForce);
}

void ABall::Jump()
{
	auto RayEnd = GetActorLocation() + MyMesh->GetCollisionShape().GetExtent().Z * FVector::DownVector;

	DrawDebugLine(GetWorld(), GetActorLocation(), RayEnd, FColor::Red, false, 2);
	
	if (GetWorld()->LineTraceTestByChannel(GetActorLocation(), RayEnd, ECC_GameTraceChannel1))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), JumpSound);
		MyMesh->AddImpulse(FVector::UpVector * JumpForce);
	}
}

void ABall::ResetPlayer() {
	if (BallController->CurrentLives > 0) BallController->OnLoseLife();
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (Input != nullptr)
	{
		// Binding de las acciones
		// Al triggerear (de forma continua) la accion MoveAction, se llama a la funcion Move
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABall::Move);
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ABall::Jump);
		Input->BindAction(ResetAction, ETriggerEvent::Started, this, &ABall::ResetPlayer);
	}
}

void ABall::Invincible()
{
	IsInvincible = true;
	float Opacity = 0.5;

	if (MyMesh)
	{
		// Almacenamos todos los materiales
		if (DynamicMaterials.Num() == 0)
		{
			for (int32 i = 0; i < MyMesh->GetNumMaterials(); i++)
			{
				UMaterialInterface* Material = MyMesh->GetMaterial(i);
				if (Material)
				{
					UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(Material, this);
					if (DynMat)
					{
						MyMesh->SetMaterial(i, DynMat);
						DynamicMaterials.Add(DynMat);
						UE_LOG(LogTemp, Warning, TEXT("Material dinámico %d creado"), i);
					}
				}
			}
		}

		// Cambiamos la opacidad de los materiales (como hay varios y no sé cuál de todos es el verdadero pues recorro)
		for (int i = 0; i < DynamicMaterials.Num(); i++)
		{
			if (DynamicMaterials[i])
			{
				DynamicMaterials[i]->SetScalarParameterValue(FName("Opacity"), Opacity);
			}
		}
	}

	FTimerHandle t;
	GetWorld()->GetTimerManager().SetTimer(t, this, &ABall::Vincible, 5, false);
}

void ABall::Vincible()
{
	IsInvincible = false;
	if (MyMesh)
	{
		for (int i = 0; i < DynamicMaterials.Num(); i++)
		{
			if (DynamicMaterials[i])
			{
				DynamicMaterials[i]->SetScalarParameterValue(FName("Opacity"), 1);
			}
		}
	}
}

void ABall::SpeedBoost()
{
	MoveForce *= 2;

	FTimerHandle t;
	GetWorld()->GetTimerManager().SetTimer(t,this, &ABall::ResetSpeed,5, false);
	
	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>(MeshComponents);
	for (UStaticMeshComponent* MeshComp : MeshComponents)
	{
		MeshComp->SetWorldScale3D(MeshComp->GetComponentScale() * 0.5f);
	}

	TArray<USpringArmComponent*> SpringArms;
	GetComponents<USpringArmComponent>(SpringArms);
	for (USpringArmComponent* SpringArm : SpringArms)
	{
		SpringArm->TargetArmLength *= 0.5f;
	}
}

void ABall::ResetSpeed()
{
	MoveForce = MoveForceInicial;

	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>(MeshComponents);
	for (UStaticMeshComponent* MeshComp : MeshComponents)
	{
		MeshComp->SetWorldScale3D(MeshComp->GetComponentScale() * 2);
	}
	
	TArray<USpringArmComponent*> SpringArms;
	GetComponents<USpringArmComponent>(SpringArms);
	for (USpringArmComponent* SpringArm : SpringArms)
	{
		SpringArm->TargetArmLength *= 2;
	}
}