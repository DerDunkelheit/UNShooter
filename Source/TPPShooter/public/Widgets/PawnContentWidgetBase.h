// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryGridWidget.h"
#include "Components/InventoryComponent.h"
#include "Widgets/GameWidgetBase.h"
#include "PawnContentWidgetBase.generated.h"

/**
 * 
 */
//This is a base class for players and robots content, there will be player's stats, inventory, skills, and robot's upgrades.
UCLASS()
class TPPSHOOTER_API UPawnContentWidgetBase : public UGameWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Stats | Inventory", meta=(ExposeOnSpawn = "true"))
	UInventoryComponent* InventoryComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Stats | Inventory", meta=(ExposeOnSpawn = "true"))
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UInventoryGridWidget* WBP_InventoryGrid;
};
