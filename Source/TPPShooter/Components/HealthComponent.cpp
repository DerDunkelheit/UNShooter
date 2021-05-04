// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	InitialHealth = 100;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = InitialHealth;

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
		Owner->OnTakePointDamage.AddDynamic(this, &UHealthComponent::TakePointDamage);
	}
}

void UHealthComponent::RestoreHealth(float Value)
{
	CurrentHealth += Value;

	if (CurrentHealth > InitialHealth)
	{
		CurrentHealth = InitialHealth;
	}
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                  AController* InstigatedBy, AActor* DamageCauser)
{
	const float DamageToDo = DamageMultiply != 0 ? Damage * DamageMultiply : Damage;
	CurrentHealth -= DamageToDo;
	DamageMultiply = 0;
	
	if(bDebugMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, FString::Printf(TEXT("CurrentHealth: %f"), CurrentHealth));
	}
	
	if (CurrentHealth <= 0)
	{
		TriggerDie();
	}
}

void UHealthComponent::TakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
	FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
	const UDamageType* DamageType, AActor* DamageCauser)
{
	if(VulnerableBonesMap.Num() > 0)
	{
		for (auto pair : VulnerableBonesMap)
		{
			if(pair.Key == BoneName.ToString())
			{
				DamageMultiply = pair.Value;
				return;
			}
		}
	}
}
