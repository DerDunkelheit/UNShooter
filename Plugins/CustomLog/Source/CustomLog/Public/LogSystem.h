// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogSystem.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMLOG_API ULogSystem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void Message(FString message, FColor messageColor);
};
