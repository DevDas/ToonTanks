// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	//TurretMesh->SetWorldRotation(LookAtTarget.Rotation());

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
}

void APawnBase::HandleDestruction()
{
	// Death Effects

	// Do Unique Child Overrides

	// pawnTurret - Inform GameMode Turret Died ,
	// Destroy
	// PawnTank -> StopMovement
}
