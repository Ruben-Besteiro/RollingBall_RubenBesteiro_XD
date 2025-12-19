// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/PowerUpGG.h"

#include "Ball.h"

void APowerUpGG::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		BallController = Cast<ABallPlayerController>(GetWorld()->GetFirstPlayerController());		// Lo que hay dentro del () nos devuelve un PlayerController genérico
		ABall* Player = Cast<ABall>(OtherActor);
		if (!Player) return;

		UStaticMeshComponent* Mesh = Player->FindComponentByClass<UStaticMeshComponent>();
		if (Mesh)
		{
			Mesh->AddForce(FVector(-1, 0, 1) * GGForce);
		}
		BallController->isGG = true;
		UE_LOG(LogTemp, Warning, TEXT("%d"), BallController->isGG);
		Destroy();
	}
}
