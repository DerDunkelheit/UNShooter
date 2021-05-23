// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TPPShooter/MinecraftCrfatingSystem/CraftingManager.h"

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

private:
	UPROPERTY(Transient)
	UCraftingManager* CraftingManagerInstance;
};
