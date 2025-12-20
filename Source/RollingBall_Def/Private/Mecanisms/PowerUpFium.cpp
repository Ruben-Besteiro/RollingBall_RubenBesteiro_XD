// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/PowerUpFium.h"
#include "Ball.h"

// Sets default values
APowerUpFium::APowerUpFium()
{
	PrimaryActorTick.bCanEverTick = true; 
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;
}

// Called when the game starts or when spawned
void APowerUpFium::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APowerUpFium::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUpFium::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		ABall* Player = Cast<ABall>(OtherActor);
		FVector Vector(FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f), 0.25);
		Vector.Normalize();
		Player->FindComponentByClass<UStaticMeshComponent>()->AddImpulse(Vector * 500000);
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
	}
}