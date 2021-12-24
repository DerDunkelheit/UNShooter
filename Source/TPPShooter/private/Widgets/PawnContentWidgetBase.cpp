// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/PawnContentWidgetBase.h"

void UPawnContentWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	bStopAction = true;
	
	//InventoryComponent exposes on spawn, when BP_PlayerController creates widget.
	WBP_InventoryGrid->InitializeGrid(InventoryComponent, TileSize);

	FOnInputAction callback;
	callback.BindDynamic(this, &UPawnContentWidgetBase::OnInventoryButtonPressed);
	//TODO: we hardcode input naming here, that's not good, we should have separate place for that, from where we can ge it.
	ListenForInputAction("OpenGridInventory", IE_Pressed, false, callback);
}

void UPawnContentWidgetBase::OnInventoryButtonPressed()
{
	APlayerController* controller = GetOwningPlayer();
	FInputModeGameOnly inputMode;
	RemoveFromParent();
	controller->SetInputMode(inputMode);
	controller->SetShowMouseCursor(false);
}
