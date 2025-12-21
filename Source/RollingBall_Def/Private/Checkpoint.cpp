#include "Checkpoint.h"
#include "Components/SphereComponent.h"
#include "Engine/PlayerStartPIE.h"
#include "Kismet/GameplayStatics.h"
#include "BallPlayerController.h"

// En el vídeo digo que el sistema de checkpoints me costó sobre todo por el tema del reseteo
ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);

	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Trigger->OnComponentBeginOverlap.AddDynamic(
		this, &ACheckpoint::NotifyActionBeginOverlap
	);
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	BallController = Cast<ABallPlayerController>(GetWorld()->GetFirstPlayerController());
}

void ACheckpoint::NotifyActionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* PlayerStart = UGameplayStatics::GetActorOfClass(
		GetWorld(),
		APlayerStart::StaticClass()
	);

	// Movemos el PlayerStart a la posición del checkpoint que acabamos de pillar
	PlayerStart->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	PlayerStart->SetActorLocation(this->GetActorLocation());

	// Actualizamos la lista de monedas que hemos pillado (por copia, no por referencia)
	BallController->CollectedSavedCoins = TArray<AGoldCube*>(BallController->CollectedCoins);

	BallController->SavedScore = BallController->CurrentScore;
}