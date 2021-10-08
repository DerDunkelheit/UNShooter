// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/public/CustomGameInstance.h"

UCustomGameInstance::UCustomGameInstance()
{
}

//TODO: Create template for that.

UCraftingManager* UCustomGameInstance::CraftingManager()
{
	return
		IsValid(CraftingManagerInstance)
			? CraftingManagerInstance
			: CraftingManagerInstance = NewObject<UCraftingManager>(this, CraftingManagerClass, FName("CraftingManager"));
}

UDialoguesManager* UCustomGameInstance::DialoguesManager()
{
	return
		IsValid(DialoguesManagerInstance)
			? DialoguesManagerInstance
			: DialoguesManagerInstance = NewObject<UDialoguesManager>(this, FName("DialoguesManager"));
}

UPersistenceManager* UCustomGameInstance::PersistenceManager()
{
	return
		IsValid(PersistenceManagerInstance)
			? PersistenceManagerInstance
			: PersistenceManagerInstance = NewObject<UPersistenceManager>(this, FName("PersistenceManager"));
}

UDataTablesParser* UCustomGameInstance::GetDataTablesParser()
{
	return
		IsValid(DataTablesParserInstance)
			? DataTablesParserInstance
			: DataTablesParserInstance = NewObject<UDataTablesParser>(this, DataTablesParserClass, FName("CraftingManager"));
}
