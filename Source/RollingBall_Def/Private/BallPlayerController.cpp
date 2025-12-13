// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPlayerController.h"

#include "Ball.h"
#include "CanvasItem.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"

void ABallPlayerController::OnLoseLife()
{
	CurrentLives--;
	UpdateUILives(CurrentLives);

	APawn* P = GetPawn();
	if (CurrentLives > 0)
	{
		UnPossess();
		P->Destroy();
		GetWorld()->GetAuthGameMode()->RestartPlayer(this);
	}
	else
	{
		GameOver();
	}
}

void ABallPlayerController::OnCollectCoin()
{
	CurrentScore += 10;

	UpdateUIScore(CurrentScore);
}

void ABallPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get the local player subsystem to add input mapping context
	auto Input = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Input->AddMappingContext(ControlsMaps, 0);
}

void ABallPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABall* BallPawn = Cast<ABall>(InPawn);
	// Yo (controlador) le digo a la bola que yo soy su controlador
	BallPawn->SetBallController(this);
}

void ABallPlayerController::GameOver()
{
	bShowMouseCursor = true;

	//mostrar widget de gameover
	auto WidgetCreated = CreateWidget(this, GameOverWidgetClass);
	WidgetCreated->AddToViewport();
}
