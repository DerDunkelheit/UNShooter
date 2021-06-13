// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MinecraftItem.h"
#include "UObject/NoExportTypes.h"
#include "CraftingManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TPPSHOOTER_API UCraftingManager : public UObject
{
	GENERATED_BODY()

public:
	UCraftingManager();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TArray<UMinecraftItem*> DefaultItems;

	UFUNCTION(BlueprintCallable)
	void Test();
};
