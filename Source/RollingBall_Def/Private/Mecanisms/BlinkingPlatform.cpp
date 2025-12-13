// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/BlinkingPlatform.h"

// Sets default values
ABlinkingPlatform::ABlinkingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Components
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);
}

// Called when the game starts or when spawned
void ABlinkingPlatform::BeginPlay()
{
	Super::BeginPlay();

	//Timer handler, UObject (dueño), delegado, tiempo de retardo, si se repite o no
	GetWorldTimerManager().SetTimer(BlinkTimerHandle, this, &ABlinkingPlatform::Blink, 2, true);

	if (!bIsActive)
	{
		PlatformMesh->SetVisibility(false);
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ABlinkingPlatform::Blink()
{
	if (PlatformMesh->IsVisible() && bIsActive)
	{
		bIsActive = false;
		PlatformMesh->SetVisibility(false);
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		bIsActive = true;
		PlatformMesh->SetVisibility(true);
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

// Called every frame
void ABlinkingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
