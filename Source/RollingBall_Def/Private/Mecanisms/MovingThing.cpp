#include "Mecanisms/MovingThing.h"

AMovingThing::AMovingThing()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingThing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Counter += DeltaTime;
	
	if (Counter >= CycleTime)
	{
		Sign = !Sign;
		Counter = 0.f;
	}

	FVector Direction;
	if (!DirectionFalseXTrueY) Direction = Sign ? FVector(1, 0, 0) : FVector(-1, 0, 0);
	else  Direction = Sign ? FVector(0, 1, 0) : FVector(0, -1, 0);
	
	AddActorLocalOffset(Direction * MoveSpeed * DeltaTime);
}