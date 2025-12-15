#include "Checkpoint.h"
#include "Components/SphereComponent.h"
#include "Engine/PlayerStartPIE.h"
#include "Kismet/GameplayStatics.h"

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
}

void ACheckpoint::NotifyActionBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	UE_LOG(LogTemp, Warning, TEXT("Algo ha entrado en el checkpoint"));
	if (!OtherActor || !OtherActor->ActorHasTag("Player"))
		return;

	UE_LOG(LogTemp, Warning, TEXT("Checkpoint activado"));

	AActor* PlayerStart = UGameplayStatics::GetActorOfClass(
		GetWorld(),
		APlayerStart::StaticClass()
	);

	PlayerStart->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	PlayerStart->SetActorLocation(this->GetActorLocation());

	UE_LOG(LogTemp, Warning, TEXT("Posición PlayerStart: %s"), *PlayerStart->GetActorLocation().ToString());
}
