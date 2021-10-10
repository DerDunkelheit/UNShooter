// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Items/Item.h"
#include "UObject/NoExportTypes.h"
#include "DataTablesParser.generated.h"

USTRUCT(BlueprintType)
struct FLootItemsRawData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UItem> ItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Probability;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TPPSHOOTER_API UDataTablesParser : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void DisplayBoxLotTable(UDataTable* DataTable);

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GetLoots(UDataTable* dataTable, int lootCount);

private:
	void CalculateTotalWeight(UDataTable* dataTable, int& totalWeightOut, TMap<FLootItemsRawData*, FString>& rawDataMapOut);
};
