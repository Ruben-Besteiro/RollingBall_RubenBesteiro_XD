// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallPlayerController.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Ball.generated.h"

UCLASS()
class ROLLINGBALL_DEF_API ABall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABall();

	void SetBallController(ABallPlayerController* BallPlayerController);
	void SetOpacity(float Opacity);
	void GoTransparent();
	void ResetTransparency();
	void SpeedBoost();
	void ResetSpeed();

protected:
	void DamageTaken();
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Movimiento de la bola
	void Move(const FInputActionValue& InputActionValue);

	// Salto de la bola
	void Jump();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(EditDefaultsOnly);
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditDefaultsOnly);
	class USpringArmComponent* MySpringArm;

	UPROPERTY(EditDefaultsOnly);
	class UCameraComponent* MyCamera;

	UPROPERTY(EditDefaultsOnly, Category="Movement Settings");
	class UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Movement Settings");
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Movement Settings");
	float MoveForce;
	float MoveForceInicial;		// Esto se usará cuando pillemos el powerup de velocidad

	UPROPERTY(EditDefaultsOnly, Category="Jump Settings");
	float JumpForce;

	UPROPERTY(EditDefaultsOnly, Category="Jump Settings");
	USoundBase* JumpSound;

	// Esto se usará para cambiar la opacidad
	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> DynamicMaterials;

	UPROPERTY();
	ABallPlayerController* BallController;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
