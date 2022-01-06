// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InventoryComponent.h"
#include "FP_FirstPerson/FP_FirstPersonCharacter.h"
#include "Kismet/KismetMathLibrary.h"
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

	FillOccupiedTilesMap();

	/*for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}*/

	for (auto& Item : DefaultItems)
	{
		TArray<FIntPoint> TilesToPlace;
		if(HasSpaceInGridInventory(Item, TilesToPlace))
		{
			AddItem(Item);
			ItemsPositions.Add(Item, FItemOccupiedTilesNested{TilesToPlace});

			//Lock occured tiles. TODO: create an event for that
			for(auto& pair : occupiedTiles)
			{
				if(TilesToPlace.FindByPredicate([&](FIntPoint& currentPoint)
				{
					return currentPoint.X == pair.Key.X && currentPoint.Y == pair.Key.Y;
				}))
				{
					occupiedTiles[pair.Key] = true;
				}
			}
		}
	}
}

void UInventoryComponent::AddItems(TArray<UItem*> NewItems)
{
	for (UItem* item : NewItems)
	{
		AddItem(item);
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


bool UInventoryComponent::HasSpaceInGridInventory(UItem* item, TArray<FIntPoint>& tilesToPlaceOut, int Index)
{
	//Index zero is the first top left tile.
	
	FTile tile = IndexToTile(Index);
	FIntPoint itemDimensions = item->Dimensions;
	FIntPoint inventoryDimensions(Columns, Rows);
	//int lastXIndex = tile.X + inventoryDimensions.X;
	//int lastYIndex = tile.Y + inventoryDimensions.Y;

	if(item->Dimensions.X > Columns || item->Dimensions.Y > Rows) return false;
	
	TArray<FIntPoint> availableTiles;
	int yFirstFoundPosition = 0;
	bool wasAtLeastOneRowFound = false;
	//vertically iterations through inventory.
	for (int i = tile.X; i < inventoryDimensions.X; i++)
	{
		//TODO: come up with naming.
		bool wasFoundInCurrentRowInPreviousIteration = false;
		int currentRowAvailableTilesFoundCount = 0;
		for (int j = tile.Y; j < inventoryDimensions.Y; j++)
		{
			if(wasAtLeastOneRowFound)
			{
				if(j < yFirstFoundPosition) continue;
			}
			
			FTile currentTile = FTile(i, j);
			if(!IsTileValid(currentTile)) return false;

			FIntPoint currentTilePoint(i, j);
			if(!occupiedTiles[currentTilePoint])
			{
				yFirstFoundPosition = j;
				wasFoundInCurrentRowInPreviousIteration = true;
				wasAtLeastOneRowFound = true;
				availableTiles.Add(currentTilePoint);
				currentRowAvailableTilesFoundCount++;
			}
			else
			{
				if(wasFoundInCurrentRowInPreviousIteration)
				{
					wasFoundInCurrentRowInPreviousIteration = false;
					wasAtLeastOneRowFound = false;
					availableTiles.Empty();
					currentRowAvailableTilesFoundCount = 0;
				}
			}

			//MoveToNextLine, because we have already fond suitable amount.
			if(currentRowAvailableTilesFoundCount == itemDimensions.Y)
			{
				yFirstFoundPosition -= currentRowAvailableTilesFoundCount - 1;
				break;
			}
		}

		//Prevent case when we found tiles but not required amount and move to next colum, for instance we got 3 * 3 size item and we found only 2 Y tiles.
		if(currentRowAvailableTilesFoundCount != itemDimensions.Y)
		{
			wasAtLeastOneRowFound = false;
			availableTiles.Empty();
		}

		//Check if we found enough tiles. 
		if(availableTiles.Num() == itemDimensions.X * itemDimensions.Y)
		{
			//We can use it as an out parameter because TArray is allocated in the heap by default.
			tilesToPlaceOut = availableTiles;
			return true;
		}
	}

	return false;
}

FTile UInventoryComponent::IndexToTile(int index)
{
	FTile returnTile;

	int x = UKismetMathLibrary::Percent_IntInt(index, Columns);
	int y = index / Columns;

	returnTile.X = x;
	returnTile.Y = y;

	return returnTile;
}

int UInventoryComponent::TileToIndex(FTile tile)
{
	return tile.X + tile.Y * Columns;
}

bool UInventoryComponent::IsTileValid(FTile tile)
{
	bool value = ((tile.X >= 0 && tile.Y >= 0) && (tile.X < Columns && tile.Y < Rows));
	return ((tile.X >= 0 && tile.Y >= 0) && (tile.X < Columns && tile.Y < Rows));
}

void UInventoryComponent::ClearInventory()
{
	Items.Empty();

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

void UInventoryComponent::ClearItemPreviousCells(UItem* Item)
{
	//TODO: create an event for that, as mentioned above.
	TArray<FIntPoint> previousTiles = ItemsPositions[Item].occupiedTiles;
	for(auto& pair : occupiedTiles)
	{
		for(auto& tile : previousTiles)
		{
			if(pair.Key.X == tile.X && pair.Key.Y == tile.Y)
			{
				occupiedTiles[pair.Key] = false;
			}
		}
	}
	//TODO: Check is item valid.
	ItemsPositions[Item].occupiedTiles.Empty();
}

void UInventoryComponent::SetNewPositionsForItem(UItem* Item, TArray<FIntPoint> tiles)
{
	ItemsPositions[Item].occupiedTiles = tiles;

	//Lock occured tiles. TODO: create an event for that
	for(auto& pair : occupiedTiles)
	{
		if(ItemsPositions[Item].occupiedTiles.FindByPredicate([&](FIntPoint& currentPoint)
		{
			return currentPoint.X == pair.Key.X && currentPoint.Y == pair.Key.Y;
		}))
		{
			occupiedTiles[pair.Key] = true;
		}
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
	auto PickUpItem = GetWorld()->SpawnActor<APickupActor>(DropItemPrefab, DropTransform.GetLocation(),
	                                                       DropTransform.Rotator());

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

int UInventoryComponent::GetColumns() const
{
	return Columns;
}

int UInventoryComponent::GetRows() const
{
	return Rows;
}

TMap<UItem*, FItemOccupiedTilesNested>& UInventoryComponent::GetItemsPositionsMap()
{
	return ItemsPositions;
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

UItem* UInventoryComponent::GetItemAtIndex(int index)
{
	check(Items.IsValidIndex(index));

	return Items[index];
}

void UInventoryComponent::AddItemAt(UItem* item, int topLeftIndex)
{
	FTile tile = IndexToTile(topLeftIndex);
	FIntPoint dimensions = item->Dimensions;
	int lastXIndex = tile.X + dimensions.X - 1;
	int lastYIndex = tile.Y + dimensions.Y - 1;

	//TODO: use ForEach algo.
	for (int i = tile.X; i < lastXIndex; i++)
	{
		for (int j = tile.Y; j < lastYIndex; j++)
		{
			FTile currentTile = FTile(i, j);

			Items.Insert(item, TileToIndex(currentTile));
		}
	}
}

void UInventoryComponent::FillOccupiedTilesMap()
{
	FTile tile = IndexToTile(0);
	FIntPoint inventoryDimensions(Columns, Rows);
	int lastXIndex = tile.X + inventoryDimensions.X;
	int lastYIndex = tile.Y + inventoryDimensions.Y;

	//vertically iterations through inventory.
	for (int i = tile.X; i < lastXIndex; i++)
	{
		for (int j = tile.Y; j < lastYIndex; j++)
		{
			FTile currentTile = FTile(i, j);
			
			check(IsTileValid(currentTile));

			//TODO: remember about save/load items.
			occupiedTiles.Add(FIntPoint(currentTile.X, currentTile.Y), false);
		}
	}
}
