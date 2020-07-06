// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"

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
}

void APawnBase::RotateTurret(FVector LookAtTarget)
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
	OnFire.Broadcast();
	// Spawn Projectile

	if (!ProjectileClass) return;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform());
	Projectile->SetOwner(this);
}

void APawnBase::HandleDestruction()
{
	// Death Effects

	// Do Unique Child Overrides

	// pawnTurret - Inform GameMode Turret Died ,
	// Destroy
	// PawnTank -> StopMovement
}
