// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTankGameModeBase.h"

void AToonTankGameModeBase::BeginPlay()
{
	// Get Reference Win/Lose
	// Call HandleStart , Start CounDown, Turret Activision
}

void AToonTankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check WhatActor Dead
}

void AToonTankGameModeBase::HandleGameStart()
{
	GameStart();

	// Initialize Start Condition
}

void AToonTankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);

	// See If Player Destroyed//else if Turret Destroyed
}
