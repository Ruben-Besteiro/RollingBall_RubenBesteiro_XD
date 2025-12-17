#include "Mecanisms/GoldCube.h"
#include "Components/StaticMeshComponent.h"

AGoldCube::AGoldCube()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AGoldCube::BeginPlay()
{
	Super::BeginPlay();
}

void AGoldCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(RotationSpeed * DeltaTime, RotationSpeed * DeltaTime, 0));
}