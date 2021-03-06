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

	if (PlayerTank && ReturnDistanceToPlayer() <= FireRange && PlayerTank->GetPlayerAlive())
	{
		RotateTurret(PlayerTank->GetActorLocation()); //**********************
	}
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
	if (!PlayerTank) return;

	//If Player In Range Then Fire
	if (ReturnDistanceToPlayer() <= FireRange && PlayerTank->GetPlayerAlive())
	{
		//Fire Method Of PawnBase
		Fire();
	}
}

 float APawnTurret::ReturnDistanceToPlayer()
{
	 if (!PlayerTank) return 0.f;

	 return (PlayerTank->GetActorLocation() - GetActorLocation()).Size();
}

 void APawnTurret::HandleDestruction()
 {
	 Super::HandleDestruction();

	 Destroy();
 }