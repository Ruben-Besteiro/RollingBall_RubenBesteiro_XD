#pragma once

#include "Ball.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombEnemy.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ROLLINGBALL_DEF_API ABombEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values
	ABombEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyHit(
		UPrimitiveComponent* MyComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Stuff")
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Stuff")
	USphereComponent* SphereTrigger;

	UPROPERTY(EditAnywhere, Category = "Stuff")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Stuff")
	UParticleSystem* Particles;
	
	ABall* Player;
	FVector FollowPos;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FTimerHandle FlashTimer;
	bool IsRed = true;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* RedMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* WhiteMaterial;

	UPROPERTY(EditAnywhere)
	USoundBase* TickSound;

	UPROPERTY(EditAnywhere)
	USoundBase* BoomSound;

	UFUNCTION()
	void FlashMaterial();
};