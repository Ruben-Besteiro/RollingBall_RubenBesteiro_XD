// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_PushingCylinder.generated.h"

UCLASS()
class ROLLINGBALL_DEF_API ABP_PushingCylinder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_PushingCylinder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category="Components")
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UStaticMeshComponent* CylinderMesh;

	UPROPERTY(EditDefaultsOnly, Category="Rotation Settings")
	float ImpulseForce = 1000.f;
};
