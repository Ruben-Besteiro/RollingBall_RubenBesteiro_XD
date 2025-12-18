#include "Mecanisms/BombEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ABombEnemy::ABombEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MyMesh);
	
	SphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SphereTrigger->SetupAttachment(MyMesh);

	SphereTrigger->OnComponentBeginOverlap.AddDynamic(
		this, &ABombEnemy::OnOverlap
	);

	SphereTrigger->OnComponentEndOverlap.AddDynamic(
		this, &ABombEnemy::OnEndOverlap
	);
}

void ABombEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABombEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Player != nullptr)
	{
		FollowPos = FVector(Player->GetActorLocation().X, Player->GetActorLocation().Y, this->GetActorLocation().Z);		// Sigue al jugador pero solo en el plano XY
		FVector Direction = (FollowPos - GetActorLocation()).GetSafeNormal();
		SetActorLocation(GetActorLocation() + Direction * MoveSpeed * DeltaTime);
	}
}

void ABombEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		Player = Cast<ABall>(OtherActor);
	}
}

void ABombEnemy::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		Player = nullptr;
	}
}

void ABombEnemy::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Other && Other->ActorHasTag("Player"))
	{
		FVector Fium = (Other->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		if (Player != nullptr)
		{
			Player->FindComponentByClass<UStaticMeshComponent>()->AddImpulse(Fium * 500000);
			Destroy();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles, Hit.Location);
		}
		Player = nullptr;
	}
}