// Fill out your copyright notice in the Description page of Project Settings.


#include "Mecanisms/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;		// No habrá Tick
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMesh"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	SetRootComponent((ProjectileMesh));		// Hacemos que el modelo sea el padre de todo

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//ProjectileMesh->AddForce();
	// Las partículas acompañan al componente
	UGameplayStatics::SpawnEmitterAttached(TrailParticles, ProjectileMesh, NAME_None, FVector(ForceInit),
		FRotator::ZeroRotator, FVector(1)), EAttachLocation::KeepRelativeOffset, false;
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::ProjectileHits);
	
}

void AProjectile::ProjectileHits(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	this->Destroy();
	// Las partículas aparecen en un sitio
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, Hit.Location);
	UGameplayStatics::ApplyDamage(OtherActor, 1, nullptr, this, UDamageType::StaticClass());
}
