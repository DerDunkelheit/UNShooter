// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/DataTablesParser.h"
#include "Kismet/DataTableFunctionLibrary.h"

void UDataTablesParser::DisplayBoxLotTable(UDataTable* DataTable)
{
	TArray<FName> rowNames = DataTable->GetRowNames();
	for (auto name : rowNames)
	{
		FLootItemsRawData* rawData = DataTable->FindRow<FLootItemsRawData>(name, "");
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange,FString::Printf(TEXT("%s probability: %d"), *name.ToString(), rawData->Probability));
	}
}

TArray<FString> UDataTablesParser::GetLoots(UDataTable* DataTable, int LootCount)
{
    TArray<FString> returnLoot;
	int totalWeight;
	TMap<FLootItemsRawData*, FString> allRawMap;
	
	CalculateTotalWeight(DataTable, totalWeight, allRawMap);

	for (int i = 0; i < LootCount; i++)
	{
		int randomValue = FMath::RandRange(0, totalWeight);
		for(auto pair : allRawMap)
		{
			if(randomValue < pair.Key->Probability)
			{
				returnLoot.Add( pair.Value + " " + FString::FromInt(pair.Key->Probability));
				break;
			}

			randomValue -= pair.Key->Probability;
		}
	}

	return returnLoot;
}

void UDataTablesParser::CalculateTotalWeight(UDataTable* dataTable, int& totalWeightOut,
	TMap<FLootItemsRawData*, FString>& rawDataMapOut)
{
	totalWeightOut = 0;
	TArray<FName> rowNames = dataTable->GetRowNames();
	for (auto name : rowNames)
	{
		FLootItemsRawData* rawData = dataTable->FindRow<FLootItemsRawData>(name, "");
		rawDataMapOut.Add(rawData, name.ToString());
		totalWeightOut += rawData->Probability;
	}
}
