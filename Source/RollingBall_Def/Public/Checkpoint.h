#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class AGoldCube;
class ABallPlayerController;
class USphereComponent;

UCLASS()
class ROLLINGBALL_DEF_API ACheckpoint : public AActor
{
	GENERATED_BODY()

public:
	ACheckpoint();
	int SavedScore = 0;

protected:
	virtual void BeginPlay() override;

private:
	ABallPlayerController* BallController;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Trigger;

	UFUNCTION()
	void NotifyActionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};