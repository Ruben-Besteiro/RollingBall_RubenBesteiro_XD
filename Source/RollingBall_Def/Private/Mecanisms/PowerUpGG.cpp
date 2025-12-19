// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/PowerUpGG.h"

#include "Ball.h"

void APowerUpGG::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		ABall* Player = Cast<ABall>(OtherActor);
		if (!Player) return;

		UStaticMeshComponent* Mesh = Player->FindComponentByClass<UStaticMeshComponent>();
		if (Mesh)
		{
			Mesh->AddForce(FVector(-1, 0, 1) * GGForce);
		}
		isGG = true;
		Destroy();
	}
}
