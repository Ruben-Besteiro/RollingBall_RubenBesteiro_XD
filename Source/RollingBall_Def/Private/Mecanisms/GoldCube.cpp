// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/GoldCube.h"

// Sets default values
AGoldCube::AGoldCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoldCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoldCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(Rotator * DeltaTime);
}

