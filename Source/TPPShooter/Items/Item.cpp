// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"

UItem::UItem()
{
	Weight = 1.0f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
	Quantity = 1;
}

void UItem::Use(ATPPShooterCharacter* Character)
{
	OnUse(Character);
}
