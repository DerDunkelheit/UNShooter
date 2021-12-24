// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PawnContentWidgetBase.h"

void UPawnContentWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	//InventoryComponent exposes on spawn, when BP_PlayerController creates widget.
	WBP_InventoryGrid->Initialize(InventoryComponent, TileSize);
}
