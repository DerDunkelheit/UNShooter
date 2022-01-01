// Fill out your copyright notice in the Description page of Project Settings.

#include "TPPShooter/public/Items/Item.h"

UItem::UItem()
{
	Weight = 1.0f;
	ItemDisplayName = FText::FromString("Item");
	bCanBeUsed = true;
	UseActionText = FText::FromString("Use");
	Quantity = 1;
}

UMaterialInterface* UItem::GetIcon()
{
	return bRotated ? GridIconRotated : GridIcon;
}

void UItem::Use(AFP_FirstPersonCharacter* Character)
{
	OnUse(Character);
}

FIntPoint UItem::GetDimensions()
{
	return Dimensions;
}
