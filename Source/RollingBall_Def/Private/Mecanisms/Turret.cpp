// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/Turret.h"
#include "Components/SphereComponent.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBaseMesh"));
	TurretHeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretHeadMesh"));
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));

	SetRootComponent(TurretBaseMesh);
	TurretHeadMesh->SetupAttachment(GetRootComponent());
	SphereTrigger->SetupAttachment(GetRootComponent());
	SpawnPoint->SetupAttachment(TurretHeadMesh);

}

void ATurret::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))		// Cuando el jugador hace overlap de la esfera
	{
		Target = OtherActor;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurret::SpawnProjectile, 2, true);
	}
}

void ATurret::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))		// Cuando el jugador hace overlap de la esfera
	{
		Target = nullptr;
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void ATurret::SpawnProjectile()
{
	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation());
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	SphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlap);		// Cuando se llame al overlap de la esfera, llamamos al método OnOverlap
	SphereTrigger->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnEndOverlap);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Obtenemos la direccion del target, la normalizamos, la interpolamos y la torreta gira hacia el target
	if (Target)
	{
		FVector LookDir = (Target->GetActorLocation() - this->GetActorLocation()).GetSafeNormal();
		FVector InterpVector = FMath::VInterpTo(TurretHeadMesh->GetForwardVector(), LookDir, DeltaTime, RotationSpeed);
		FRotator TargetRotator = InterpVector.Rotation();
		TurretHeadMesh->SetWorldRotation(FRotator(0.f, TargetRotator.Yaw, 0.f));
	}

}

