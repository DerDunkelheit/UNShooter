// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"

// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	MaxAmmo = 30;

	bUseAmmo = true;
}

// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = InitialAmmo;
}

void UAmmoComponent::SetNewMaxAmmo(int Value)
{
	MaxAmmo = Value;
}

bool UAmmoComponent::HasAmmo()
{
	if(!bUseAmmo) return true;

	return CurrentAmmo > 0;
}

void UAmmoComponent::ConsumeAmmo(int Amount)
{
	CurrentAmmo -= Amount;

	if(CurrentAmmo < 0)
	{
		CurrentAmmo = 0;
	}
}

bool UAmmoComponent::TryReload()
{
	//TODO: check ammo in player inventory.

	CurrentAmmo += 30;
	if(CurrentAmmo > MaxAmmo) CurrentAmmo = MaxAmmo;
	return true;
}

