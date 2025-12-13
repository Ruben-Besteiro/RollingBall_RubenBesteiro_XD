// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/MovingPlatform.h"

#include "Components/SplineComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Componentes del actor
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));

	// Jerarquia de componentes
	SetRootComponent(Root);
	PlatformMesh->SetupAttachment(Root);
	Spline->SetupAttachment(Root);

	// Config de físicas
	PlatformMesh->SetSimulatePhysics(true);
	PlatformMesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	PointsCount = Spline->GetNumberOfSplinePoints();
	CalculateNewDestination();
	PlatformMesh->SetPhysicsLinearVelocity(CurrentDirection * Speed);
}

void AMovingPlatform::CalculateNewDestination()
{
	CurrentDestination = Spline->GetLocationAtSplinePoint(CurrentIndex, ESplineCoordinateSpace::World);	
	CurrentDirection = (CurrentDestination - PlatformMesh->GetComponentLocation()).GetSafeNormal();

	// Asegura que CurrentIndex no supere el numero de puntos
	CurrentIndex = (CurrentIndex + 1) % PointsCount;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FVector::Distance(PlatformMesh->GetComponentLocation(), CurrentDestination) < 10)
	{
		CalculateNewDestination();
		PlatformMesh->SetPhysicsLinearVelocity(CurrentDirection * Speed);
	}

}

