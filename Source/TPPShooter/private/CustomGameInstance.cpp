// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/public/CustomGameInstance.h"

UCustomGameInstance::UCustomGameInstance()
{
}

UCraftingManager* UCustomGameInstance::CraftingManager()
{
	return
		IsValid(CraftingManagerInstance)
			? CraftingManagerInstance
			: CraftingManagerInstance = NewObject<UCraftingManager>(this, CraftingManagerClass, FName("CraftingManager"));
}
