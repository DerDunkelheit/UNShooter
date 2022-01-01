// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemWidget.h"

void UItemWidget::SetInitialProperties(float tileSize, UItem* item)
{
	TileSize = tileSize;
	Item = item;
}
