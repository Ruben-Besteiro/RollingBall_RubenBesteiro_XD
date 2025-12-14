// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/PowerUpInv.h"

#include "Ball.h"

// Sets default values
APowerUpInv::APowerUpInv()
{
	PrimaryActorTick.bCanEverTick = true; 
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;
}

// Called when the game starts or when spawned
void APowerUpInv::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpInv::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUpInv::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		ABall* Player = Cast<ABall>(OtherActor);
		Player->Invincible();
		Destroy();
	}
}