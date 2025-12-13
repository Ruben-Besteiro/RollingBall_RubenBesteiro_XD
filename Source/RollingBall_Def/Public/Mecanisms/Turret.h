// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class ROLLINGBALL_DEF_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "TurretComponents")
	UStaticMeshComponent* TurretBaseMesh;

	UPROPERTY(EditDefaultsOnly, Category = "TurretComponents")
	UStaticMeshComponent* TurretHeadMesh;

	UPROPERTY(EditDefaultsOnly, Category = "TurretComponents")
	class USphereComponent* SphereTrigger;

	UPROPERTY(EditDefaultsOnly, Category = "TurretComponents")
	TSubclassOf<class AProjectile> ProjectileClass;		// Referencia al proyectil para instanciarlo luego

	UPROPERTY(EditDefaultsOnly, Category = "TurretComponents")
	AActor* Target = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "TurretComponents")
	USceneComponent* SpawnPoint;		// USceneComponent = Empty

	UPROPERTY(EditDefaultsOnly, Category = "Turret Data")
	float RotationSpeed = 5.f;

	FTimerHandle TimerHandle;

	void SpawnProjectile();
};
