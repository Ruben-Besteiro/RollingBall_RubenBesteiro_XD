// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class ROLLINGBALL_DEF_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
#pragma region Components
	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, Category="Components")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category="Components")
	class USplineComponent* Spline;
#pragma endregion

#pragma region PlatformProperties
	UPROPERTY(EditDefaultsOnly, Category="Moving Platform")
	int32 PointsCount;

	UPROPERTY(EditDefaultsOnly, Category="Moving Platform")
	int32 CurrentIndex;

	UPROPERTY(EditDefaultsOnly, Category="Moving Platform")
	float Speed;

	UPROPERTY(EditDefaultsOnly, Category="Moving Platform")
	FVector CurrentDestination;

	UPROPERTY(EditDefaultsOnly, Category="Moving Platform")
	FVector CurrentDirection;
	
	void CalculateNewDestination();

#pragma endregion
};
