// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemWidget.h"

void UItemWidget::SetInitialProperties(float tileSize, UItem* item)
{
	TileSize = tileSize;
	Item = item;
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitialColor = BackgroundBorder->BrushColor;
}

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	BackgroundBorder->SetBrushColor(HighlightColor);
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	BackgroundBorder->SetBrushColor(InitialColor);
}
