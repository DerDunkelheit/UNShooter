// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TPPShooter/DialoguesSystem/DialoguesManager.h"
#include "TPPShooter/MinecraftCrfatingSystem/CraftingManager.h"
#include "TPPShooter/Systems/PersistenceManager.h"
#include "Systems/DataTablesParser.h"

#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCustomGameInstance();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Classes")
	TSubclassOf<UCraftingManager> CraftingManagerClass;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Classes")
	TSubclassOf<UDataTablesParser> DataTablesParserClass;

	UFUNCTION(BlueprintPure, Category = "Persistence",meta = (DisplayName = "Get Crafting Manager", Keywords = "CraftingManager"))
	UCraftingManager* CraftingManager();

    UFUNCTION(BlueprintPure, Category = "Persistence")
	UDialoguesManager* DialoguesManager();

	UFUNCTION(BlueprintPure, Category = "Persistence")
	UPersistenceManager* PersistenceManager();

	UFUNCTION(BlueprintPure, Category = "Persistence")
	UDataTablesParser* GetDataTablesParser();
	
private:
	UPROPERTY(Transient)
	UCraftingManager* CraftingManagerInstance;

	UPROPERTY(Transient)
	UDialoguesManager* DialoguesManagerInstance;

	UPROPERTY(Transient)
	UPersistenceManager* PersistenceManagerInstance;

	UPROPERTY(Transient)
	UDataTablesParser* DataTablesParserInstance;
};
