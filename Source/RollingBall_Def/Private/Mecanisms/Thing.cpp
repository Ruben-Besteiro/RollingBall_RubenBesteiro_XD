#include "Mecanisms/Thing.h"

#include "Ball.h"
#include "Kismet/GameplayStatics.h"

AThing::AThing()
{
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MyMesh);
}

void AThing::BeginPlay()
{
	Super::BeginPlay();
}

void AThing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AThing::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		ABall* Ball = Cast<ABall>(OtherActor);
		UGameplayStatics::ApplyDamage(Ball, 1, nullptr, this, UDamageType::StaticClass());
	}
}

