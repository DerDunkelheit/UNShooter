// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/MinecraftCrfatingSystem/CraftingManager.h"

#include "Items/Item.h"

UCraftingManager::UCraftingManager()
{
}

void UCraftingManager::Test()
{
	auto FoundItem = DefaultItems.FindByPredicate([](UMinecraftItem* item)
	{
		return item->ItemName.EqualTo(FText::FromString("Wood"));
	});
	//When you get that thing, you have to dereference it. auto item = *FoundItem;

	if (FoundItem == nullptr)
	{
		
	}
}
