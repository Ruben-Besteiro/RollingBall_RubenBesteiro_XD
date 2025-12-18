#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoldCube.generated.h"

UCLASS()
class ROLLINGBALL_DEF_API AGoldCube : public AActor
{
	GENERATED_BODY()

public:
	AGoldCube();

	UPROPERTY(EditAnywhere)
	int CoinID;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="R")
	FRotator Rotator = FRotator(0, 0, 0);

	UPROPERTY(EditAnywhere, Category = "R")
	float RotationSpeed;
};
