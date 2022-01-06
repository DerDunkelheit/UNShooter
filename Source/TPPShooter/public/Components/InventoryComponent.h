// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structures/Tile.h"
#include "TPPShooter/Actors/PickupActor.h"
#include "TPPShooter/Enums/AmmoTypeEnum.h"

#include "InventoryComponent.generated.h"

//Blueprints will bind to this to update the UI.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

//We have to use this, because unreal doesn't hearer tool doesn't support nested containers.
USTRUCT()
struct FItemOccupiedTilesNested
{
	GENERATED_BODY()

	TArray<FIntPoint> occupiedTiles;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	TSubclassOf<class APickupActor> DropItemPrefab;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory | Grid")
	int Columns;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory | Grid")
	int Rows;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

    UFUNCTION(BlueprintCallable)
	int GetAmmoQuantity(AmmoTypeEnum AmmoType);

	UFUNCTION(BlueprintCallable)
	void AddItems(TArray<UItem*> NewItems);
	
	UFUNCTION(BlueprintCallable)
	void AddItem(class UItem* Item);
	
	UFUNCTION(BlueprintCallable)
	bool HasSpaceInGridInventory(UItem* item, TArray<FIntPoint>& tilesToPlaceOut, int Index = 0);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTile IndexToTile(int index);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int TileToIndex(FTile tile);

	UFUNCTION(BlueprintCallable)
	bool IsTileValid(FTile tile);

	UFUNCTION(BlueprintCallable)
	void ClearInventory();

	UFUNCTION(BlueprintCallable)
	void RemoveItem(class UItem* Item);

	UFUNCTION(BlueprintCallable)
	void ClearItemPreviousCells(UItem* Item);
	UFUNCTION(BlueprintCallable)
	void SetNewPositionsForItem(UItem* Item, TArray<FIntPoint> tiles);
	
	void DropItem(class UItem* Item);
	class UAmmoItem* TryGetAmmoItem(AmmoTypeEnum AmmoType);
	int RequestAmmoFromInventory(class UAmmoItem* AmmoItem, int RequestedQuantity);
	
	int GetColumns() const;
	int GetRows() const;

	TMap<UItem*, FItemOccupiedTilesNested>& GetItemsPositionsMap();

private:
	//We use map, because we want to have O(1) access, because we have already n^2 iteration speed.
	//We use FIntPoint because FTile doesn't support GetTypeHash
	UPROPERTY()
	TMap<FIntPoint, bool> occupiedTiles;
	UPROPERTY()
	TMap<UItem*, FItemOccupiedTilesNested> ItemsPositions;
	
private:
	int CalculateRequestedAmmo(class UAmmoItem* AmmoItem, int RequestedQuantity);
	UAmmoItem* FindAmmoItem(AmmoTypeEnum AmmoType);
	UItem* GetItemAtIndex(int index);
	void AddItemAt(UItem* item, int topLeftIndex);

	void FillOccupiedTilesMap();
};
