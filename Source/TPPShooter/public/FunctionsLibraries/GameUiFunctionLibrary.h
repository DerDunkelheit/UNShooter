// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUiFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API UGameUiFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="UIUtilities")
	static void MousePositionInTile(float TileSize, float MousePositionX, float MousePositionY, bool& RightSideOut, bool& DownSideOut);
};
