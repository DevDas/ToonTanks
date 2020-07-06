// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFire);

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

	void RotateTurret(FVector LookAtTarget);

	void Fire();

	UStaticMeshComponent* GetTurretMesh() { return TurretMesh; };

	UPROPERTY(BlueprintAssignable)
	FOnFire OnFire;

protected:

	virtual void HandleDestruction();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta =(AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta =(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta =(AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta =(AllowPrivateAccess = "true"))
	class USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	//Hold Alt Key , Click Multiple Lines
};
