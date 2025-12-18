// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallPlayerController.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_DEF_API AWall: public AActor
{
	GENERATED_BODY()
public:
	AWall();

private:
	UFUNCTION()
	void BeginPlay();

	UFUNCTION()
	void Tick(float DeltaTime);
	
	UPROPERTY(EditAnywhere, Category="Stuff")
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere, Category="Stuff")
	int TargetScore;

	UPROPERTY(EditAnywhere, Category="Stuff")
	USoundBase* PassSound;
	
	UFUNCTION()
	void CheckTargetScore();

	ABallPlayerController* BallController;
};
