// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/InventoryGridWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetInputLibrary.h"
#include "Widgets/ItemWidget.h"

void UInventoryGridWidget::InitializeGrid(UInventoryComponent* inventoryComponent, float tileSize)
{
	InventoryComponent = inventoryComponent;
	InventoryComponent->OnInventoryUpdated.AddDynamic(this, &UInventoryGridWidget::Refresh);
	TileSize = tileSize;
	
	UCanvasPanelSlot* canvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	int sizeX = inventoryComponent->GetColumns() * tileSize;
	int sizeY = inventoryComponent->GetRows() * tileSize;
	canvasPanelSlot->SetSize(FVector2D(sizeX, sizeY));
	
	CreateLineSegments();
	Refresh();
}

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryGridWidget::NativeDestruct()
{
	Super::NativeDestruct();

	GridCanvasPanel->ClearChildren();
	InventoryComponent->OnInventoryUpdated.RemoveDynamic(this, &UInventoryGridWidget::Refresh);
}

bool UInventoryGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	FVector2D mousePosition = USlateBlueprintLibrary::AbsoluteToLocal(
		InGeometry, UKismetInputLibrary::PointerEvent_GetScreenSpacePosition(InDragDropEvent));
	
	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
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

void UInventoryGridWidget::Refresh()
{
	auto& positionMap = InventoryComponent->GetItemsPositionsMap();
	
	GridCanvasPanel->ClearChildren();
	for(auto& pair : positionMap)
	{
		UItemWidget* itemWidget = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemWidgetClass);
		itemWidget->SetInitialProperties(TileSize, pair.Key);
		UCanvasPanelSlot* panelSlot  = Cast<UCanvasPanelSlot>(GridCanvasPanel->AddChild(itemWidget));
		panelSlot->SetAutoSize(true);

		FIntPoint topLeftTile = pair.Value.occupiedTiles[0];
		
		panelSlot->SetPosition(FVector2D(topLeftTile.X * TileSize, topLeftTile.Y * TileSize));
	}
}