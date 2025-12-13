// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/BP_PushingCylinder.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ABP_PushingCylinder::ABP_PushingCylinder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Componentes del actor
	CylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderMesh"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Jerarquia de componentes
	SetRootComponent(Root);
	CylinderMesh->SetupAttachment(Root);

	// Config de físicas
	CylinderMesh->SetSimulatePhysics(true);
	CylinderMesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ABP_PushingCylinder::BeginPlay()
{
	Super::BeginPlay();

	//En unity: rb.AddTorque(Vector, Force);
	CylinderMesh->AddAngularImpulseInDegrees(FVector::UpVector * ImpulseForce, NAME_None, true);
}

// Called every frame
void ABP_PushingCylinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

