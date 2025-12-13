// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/PowerUpSpd.h"

#include "Ball.h"

// Sets default values
APowerUpSpd::APowerUpSpd()
{
	PrimaryActorTick.bCanEverTick = true; 
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;
}

// Called when the game starts or when spawned
void APowerUpSpd::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpSpd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUpSpd::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		ABall* Player = Cast<ABall>(OtherActor);
		Player->SpeedBoost();
		Destroy();
	}
}