// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlinkingPlatform.generated.h"

UCLASS()
class ROLLINGBALL_DEF_API ABlinkingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlinkingPlatform();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
#pragma region Components

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UStaticMeshComponent* PlatformMesh;
	
#pragma endregion

	UPROPERTY(EditDefaultsOnly, Category="Variables")
	FTimerHandle BlinkTimerHandle;

	UPROPERTY(EditInstanceOnly, Category="Variables")
	bool bIsActive;
	
	void Blink();
};
