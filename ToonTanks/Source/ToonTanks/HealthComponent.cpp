// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "ToonTankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTurret.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Health = DefaultHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GameModeRef = Cast<AToonTankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())); //*****************
	Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage,
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0 || Health == 0) return;
	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);

	if (Health <= 0)
	{
		if (GameModeRef)
		{
			GameModeRef->ActorDied(Owner);
		}
	}
}