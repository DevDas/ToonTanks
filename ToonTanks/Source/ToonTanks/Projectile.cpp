// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "Camera/CameraShake.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	TracerFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TracerFX"));
	TracerFX->AttachTo(ProjectileMesh);

	InitialLifeSpan = 3.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (!FireSound) return;
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSound, GetActorLocation());
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner) return;

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
	}

	if (HitFX && HitSound)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, HitComponent->GetComponentLocation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, HitComponent->GetComponentLocation());
	}
	if (HitShake)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HitShake, 1); //******************************
	}

	Destroy();
}