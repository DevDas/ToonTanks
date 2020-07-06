// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

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

}

void APawnTurret::CheckFireCondition()
{
	// If Player valid || s Dead hen Bail


	//If Player In Range Then Fire
}