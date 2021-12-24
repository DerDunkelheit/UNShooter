// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryGridWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UInventoryGridWidget::InitializeGrid(UInventoryComponent* inventoryComponent, float tileSize)
{
	InventoryComponent = inventoryComponent;
	TileSize = tileSize;
	
	UCanvasPanelSlot* canvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	int sizeX = inventoryComponent->GetColumns() * tileSize;
	int sizeY = inventoryComponent->GetRows() * tileSize;
	canvasPanelSlot->SetSize(FVector2D(sizeX, sizeY));
	
	CreateLineSegments();
}

void UInventoryGridWidget::CreateLineSegments()
{
	for(int i = 0 ; i <= InventoryComponent->GetColumns(); i ++)
	{
		int x = i * TileSize;
		Lines.Add(FLine(FVector2D(x,0), FVector2D(x, InventoryComponent->GetRows() * TileSize)));
	}

	for(int i = 0 ; i <= InventoryComponent->GetRows(); i ++)
	{
		int y = i * TileSize;
		Lines.Add(FLine(FVector2D(0,y), FVector2D(InventoryComponent->GetColumns() * TileSize, y)));
	}
}
