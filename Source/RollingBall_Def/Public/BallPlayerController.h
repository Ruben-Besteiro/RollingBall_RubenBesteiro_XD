// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "Mecanisms/GoldCube.h"
#include "Components/AudioComponent.h"
#include "Components/Widget.h"
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
	ABallPlayerController();
	void OnLoseLife();
	void OnCollectCoin(AGoldCube* Coin);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUILives(int32 NewLives);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUIScore(int32 NewScore);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUITime(int32 NewSeconds);

	UFUNCTION(BlueprintImplementableEvent)
	void GG();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLives = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data", meta = (AllowPrivateAccess = "true"))
	int32 CurrentScore = 0;

	int32 SavedScore = 0;
	bool isGG = false;

	UPROPERTY(EditAnywhere, Category = "Music");
	UAudioComponent* MusicComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Particles");
	UParticleSystem* Dust;

	UPROPERTY()
	TArray<class AGoldCube*> CollectedCoins;
	UPROPERTY()
	TArray<class AGoldCube*> CollectedSavedCoins;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Llamado cuando el controlador posee un pawn
	virtual void OnPossess(APawn* InPawn) override;

private:
	float Counter;
	int32 Seconds;
	
	UPROPERTY(EditAnywhere, Category = "Inputs")
	class UInputMappingContext* ControlsMaps;

	// Como blueprintreadonly solo se puede hacer en publico, incluimos lo de  meta para que pueda ser privada la var
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Data", meta = (AllowPrivateAccess = "true"))
    int32 CurrentTime = 100;

	UPROPERTY(EditAnywhere, Category="Music");
	USoundBase* Music;

	UPROPERTY(EditAnywhere, Category = "Music");
	USoundBase* LoseMoneySound;
	
	UPROPERTY(EditAnywhere, Category="Game Over Data")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Game Over Data")
	USoundBase* GameOverSound;

	// Esto es necesario para soltar las monedas que perdemos
	UPROPERTY(EditAnywhere, Category = "E")
	TSubclassOf<AActor> E;

	UFUNCTION()
	void OnMusicFinished();

	void GameOver();
};
