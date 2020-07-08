// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTankGameModeBase.h"
#include "PawnTank.h"
#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllerBase.h"

void AToonTankGameModeBase::BeginPlay()
{
	TargetTurets = GetTargetTurretCount();//************

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();

	Super::BeginPlay();
}

void AToonTankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->PawnDestroyed();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		Score += AddScore;
		
		DestroyedTurret->PawnDestroyed();
		TargetTurets--;
		if (TargetTurets == 0)
		{
			HandleGameOver(true);
		}
	}

}

int32 AToonTankGameModeBase::GetTargetTurretCount()
{
	TSubclassOf<APawnTurret>ClassToFind;
	ClassToFind = APawnTurret::StaticClass();
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);

	return TurretActors.Num();
}

void AToonTankGameModeBase::HandleGameStart()
{
	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle EnablePlayerHandle; // ***************************
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState,true);

		GetWorldTimerManager().SetTimer(EnablePlayerHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void AToonTankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}
