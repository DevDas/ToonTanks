// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Camera/CameraShake.h"

// Sets default values
APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->AttachTo(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	ProjectileSpawnPoint->AttachTo(TurretMesh);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

void APawnBase::RotateTurret(FVector LookAtTarget) //************************************
{
	// Update Turret Mesh Rotation
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(
		StartLocation, 
		FVector(LookAtTarget.X, LookAtTarget.Y,TurretMesh->GetComponentLocation().Z));

	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	if (Ammo <= 0) return;

	OnFire.Broadcast();
	// Spawn Projectile

	if (!ProjectileClass) return;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform());
	Projectile->SetOwner(this);
}

void APawnBase::PawnDestroyed()
{
	HandleDestruction();
}

void APawnBase::HandleDestruction()
{
	// Death Effects
	if (DeathFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathFX, GetActorTransform());
	}

	if (!DeathSound) return;
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DeathSound, GetActorLocation());

	if (DeathShake)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(DeathShake, 1); //******************************
	}
}
