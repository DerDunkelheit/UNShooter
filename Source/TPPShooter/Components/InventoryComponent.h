// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPPShooter/Actors/PickupActor.h"
#include "TPPShooter/Enums/AmmoTypeEnum.h"


#include "InventoryComponent.generated.h"

//Blueprints will bind to this to update the UI.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPPSHOOTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> DefaultItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<class UItem*> Items;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Inventory")
	int Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
    TSubclassOf<class APickupActor> DropItemPrefab;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void AddItem(class UItem* Item);
	void RemoveItem(class UItem* Item);
	void DropItem(class UItem* Item);
	UItem* TryGetAmmoItem(AmmoTypeEnum AmmoType);
	//TODO: rename
	int GetAvailableAmmoQuantity(class UAmmoItem* AmmoItem,int RequestedQuantity);
};
