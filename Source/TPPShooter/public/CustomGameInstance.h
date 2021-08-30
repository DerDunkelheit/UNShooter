// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TPPShooter/DialoguesSystem/DialoguesManager.h"
#include "TPPShooter/MinecraftCrfatingSystem/CraftingManager.h"
#include "TPPShooter/Systems/PersistenceManager.h"

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

	UFUNCTION(BlueprintPure, Category = "Persistence",meta = (DisplayName = "Get Crafting Manager", Keywords = "CraftingManager"))
	UCraftingManager* CraftingManager();

    UFUNCTION(BlueprintPure, Category = "Persistence")
	UDialoguesManager* DialoguesManager();

	UFUNCTION(BlueprintPure, Category = "Persistence")
	UPersistenceManager* PersistenceManager();
	
private:
	UPROPERTY(Transient)
	UCraftingManager* CraftingManagerInstance;

	UPROPERTY(Transient)
	UDialoguesManager* DialoguesManagerInstance;

	UPROPERTY(Transient)
	UPersistenceManager* PersistenceManagerInstance;
};
