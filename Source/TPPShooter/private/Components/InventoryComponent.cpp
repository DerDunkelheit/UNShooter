// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "FP_FirstPerson/FP_FirstPersonCharacter.h"
#include "TPPShooter/Actors/PickupActor.h"
#include "TPPShooter/public/Items/AmmoItem.h"
#include "TPPShooter/public/Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Capacity = 20;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

void UInventoryComponent::AddItem(UItem* Item)
{
	if (Items.Num() >= Capacity || !Item)
		return;

	//TODO: simplification is required.
	if (Item->bStackable)
	{
		UItem* SameItemInInventory = nullptr;
		for (auto item : Items)
		{
			//TODO: came up with better solution.
			if (item->ItemDisplayName.ToString() == Item->ItemDisplayName.ToString())
			{
				//TODO: add stacks
				SameItemInInventory = item;
				break;
			}
		}

		if (SameItemInInventory != nullptr)
		{
			SameItemInInventory->Quantity++;
		}
		else
		{
			Item->OwningInventory = this;
			Item->World = GetWorld();
			Items.Add(Item);
		}
	}
	else
	{
		Item->OwningInventory = this;
		Item->World = GetWorld();
		Items.Add(Item);
	}

	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::RemoveItem(UItem* Item)
{
	if (!Item)
		return;

	if (Items.Contains(Item))
	{
		if (Item->bStackable && Item->Quantity > 1)
		{
			Item->Quantity -= 1;
		}
		else
		{
			Item->OwningInventory = nullptr;
			Item->World = nullptr;
			Items.Remove(Item);
		}

		OnInventoryUpdated.Broadcast();
	}
}

void UInventoryComponent::DropItem(UItem* Item)
{
	//TODO: replace to function,
	if (Item->bStackable && Item->Quantity > 1)
	{
		Item->Quantity -= 1;
	}
	else
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		Items.Remove(Item);
	}

	OnInventoryUpdated.Broadcast();

	auto Player = Cast<AFP_FirstPersonCharacter>(GetOwner());
	const FTransform& DropTransform = Player->GetItemDropTransform();
	auto PickUpItem = GetWorld()->SpawnActor<APickupActor>(DropItemPrefab, DropTransform.GetLocation(),DropTransform.Rotator());

	PickUpItem->SetItem(Item);
}

UAmmoItem* UInventoryComponent::TryGetAmmoItem(AmmoTypeEnum AmmoType)
{
	return FindAmmoItem(AmmoType);
}

int UInventoryComponent::RequestAmmoFromInventory(UAmmoItem* AmmoItem, int RequestedQuantity)
{
	if (Items.Contains(AmmoItem))
	{
		return CalculateRequestedAmmo(AmmoItem, RequestedQuantity);
	}

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "ERROR! AmmoItem wasn't found in Inventory!");
	return 0;
}

int UInventoryComponent::CalculateRequestedAmmo(UAmmoItem* AmmoItem, int RequestedQuantity)
{
	if (AmmoItem->Quantity > RequestedQuantity)
	{
		AmmoItem->Quantity -= RequestedQuantity;
		return RequestedQuantity;
	}

	const auto ReturnValue = AmmoItem->Quantity;
	AmmoItem->Quantity = 1;
	RemoveItem(AmmoItem);

	return ReturnValue;
}

int UInventoryComponent::GetAmmoQuantity(AmmoTypeEnum AmmoType)
{
	const auto AppropriateAmmo = FindAmmoItem(AmmoType);
	if (AppropriateAmmo != nullptr)
	{
		return AppropriateAmmo->Quantity;
	}

	return 0;
}

UAmmoItem* UInventoryComponent::FindAmmoItem(AmmoTypeEnum AmmoType)
{
	for (auto Item : Items)
	{
		UAmmoItem* AmmoItem = Cast<UAmmoItem>(Item);
		if (AmmoItem)
		{
			if (AmmoItem->AmmoType == AmmoType)
			{
				return AmmoItem;
			}
		}
	}
	return nullptr;
}
