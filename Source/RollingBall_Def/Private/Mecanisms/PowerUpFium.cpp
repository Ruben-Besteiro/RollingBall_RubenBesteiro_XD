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

		float Random = FMath::FRandRange(-1.0f, 1.0f);
		float Random2 = FMath::FRandRange(-1.0f, 1.0f);
		FVector Vector(Random, Random2, 0.25);
		Vector = Vector.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), Vector.X, Vector.Y, Vector.Z);
		Player->FindComponentByClass<UStaticMeshComponent>()->AddImpulse(Vector * 500000);
		Destroy();
	}
}