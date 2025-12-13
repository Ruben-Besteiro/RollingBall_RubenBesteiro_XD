// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BallPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGBALL_DEF_API ABallPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void OnLoseLife();
	void OnCollectCoin();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUILives(int32 NewLives);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUIScore(int32 NewScore);

protected:
	virtual void BeginPlay() override;

	// Llamado cuando el controlador posee un pawn
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputMappingContext* ControlsMaps;

	// Como blueprintreadonly solo se puede hacer en publico, incluimos lo de  meta para que pueda ser privada la var
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLives = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data", meta = (AllowPrivateAccess = "true"))
	int32 CurrentScore = 0;

	UPROPERTY(EditAnywhere, Category="Game Over Data")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	
	void GameOver();
};
