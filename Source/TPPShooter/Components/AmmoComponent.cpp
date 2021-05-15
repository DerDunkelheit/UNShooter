// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TPPShooter/TPPShooterCharacter.h"
#include "TPPShooter/public/Items/AmmoItem.h"

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
	auto Player = Cast<ATPPShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(Player)
	{
        if(CurrentAmmo == MaxAmmo) return false;
		
		UAmmoItem* AmmoItem = Player->GetInventoryComponent()->TryGetAmmoItem(AmmoType);
		if(AmmoItem)
		{
			int AmountToRequest = MaxAmmo - CurrentAmmo;
			CurrentAmmo += Player->GetInventoryComponent()->RequestAmmoFromInventory(AmmoItem, AmountToRequest);
			return true;
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Cyan,"Player doesn't have appropriate ammo in inventory");
	return false;
}

