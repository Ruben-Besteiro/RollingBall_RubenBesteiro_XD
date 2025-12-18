// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

#include "Kismet/GameplayStatics.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("MyMesh"));
	SetRootComponent(MyMesh);
}

void AWall::BeginPlay()
{
	Super::BeginPlay();
	BallController = Cast<ABallPlayerController>(GetWorld()->GetFirstPlayerController());		// Lo que hay dentro del () nos devuelve un PlayerController genérico
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckTargetScore();
}

void AWall::CheckTargetScore()
{
	// Si el jugador vuelve a menos que el requisito → mostrar la pared
	if (BallController->CurrentScore < TargetScore)
	{
		if (IsHidden())
		{
			UE_LOG(LogTemp, Warning, TEXT("REAPARECE LA PARED"));
			SetActorHiddenInGame(false);
			SetActorEnableCollision(true);
		}
	}

	// Si ha llegado al objetivo → esconderlo
	if (BallController->CurrentScore >= TargetScore)
	{
		if (!IsHidden())
		{
			UE_LOG(LogTemp, Warning, TEXT("DESAPARECE LA PARED"));
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			UGameplayStatics::PlaySound2D(this, PassSound);
		}
	}
}
