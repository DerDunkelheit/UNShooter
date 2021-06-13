// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MinecraftItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable, EditInlineNew, DefaultToInstanced)
class TPPSHOOTER_API UMinecraftItem : public UObject
{
	GENERATED_BODY()

public:
	UMinecraftItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UTexture2D* ItemImage;
};
