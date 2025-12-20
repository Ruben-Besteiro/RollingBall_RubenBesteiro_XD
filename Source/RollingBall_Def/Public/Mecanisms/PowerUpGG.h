// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallPlayerController.h"
#include "Mecanisms/PowerUpFium.h"
#include "PowerUpGG.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_DEF_API APowerUpGG : public APowerUpFium
{
	GENERATED_BODY()
public:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Category="Stuff")
	float GGForce;

	UPROPERTY(EditAnywhere, Category="Stuff")
	USoundBase* GGSound;

	ABallPlayerController* BallController;
};
