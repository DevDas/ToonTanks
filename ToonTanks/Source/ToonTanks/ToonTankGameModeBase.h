// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FLeveleDefaults
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Ammo = 20;
};

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	int32 Score;

public:

	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

	UPROPERTY(EditAnywhere)
		int32 AddScore = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelDefaults")
	FLeveleDefaults LevelDefaults;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameLoop", meta = (AllowPrivateAccess = "true"))
		int32 StartDelay = 3;

	int32 GetTargetTurretCount();

	int32 TargetTurets = 0;

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	class APawnTank* PlayerTank;

	class APlayerControllerBase* PlayerControllerRef;
};