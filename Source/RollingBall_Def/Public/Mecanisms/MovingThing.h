// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mecanisms/Thing.h"
#include "MovingThing.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_DEF_API AMovingThing : public AThing
{
	GENERATED_BODY()

private:
	AMovingThing();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Ñ")
	bool DirectionFalseXTrueY;

	UPROPERTY(EditAnywhere, Category="Ñ")
	float CycleTime;

	UPROPERTY(EditAnywhere, Category="Ñ")
	float MoveSpeed;

	bool Sign = false;
	float Counter = 0;
};
