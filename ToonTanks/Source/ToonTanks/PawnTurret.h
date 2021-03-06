// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
public:

	APawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckFireCondition();

	float ReturnDistanceToPlayer();

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere)
		float Delay = 2.f;

	class APawnTank* PlayerTank = nullptr;

	UPROPERTY(EditAnywhere)
	float FireRange = 20.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction() override;
};
