// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{

}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, Delay, true, false);

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::CheckFireCondition()
{
	// If Player valid || s Dead hen Bail
	if (PlayerTank)
	{

	}

	//If Player In Range Then Fire
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		//Fire
		
	}
}

 float APawnTurret::ReturnDistanceToPlayer()
{
	 if (!PlayerTank) return 0.f;

	 return (PlayerTank->GetActorLocation() - GetActorLocation()).Size();
}
