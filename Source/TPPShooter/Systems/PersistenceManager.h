// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainSaveGame.h"
#include "UObject/NoExportTypes.h"
#include "PersistenceManager.generated.h"

USTRUCT(BlueprintType)
struct FJsonDataExampleStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Json Data")
	FString ExampleStringField;
};

UCLASS(BlueprintType, Blueprintable)
class TPPSHOOTER_API UPersistenceManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Json Data")
	FJsonDataExampleStruct JsonDataExampleStruct;
	
public:
	UFUNCTION(BlueprintCallable)
	void SaveToJsonExample();

	//TODO: maybe use pointers?????
	UFUNCTION(BlueprintCallable)
	FJsonDataExampleStruct LoadJsonExample();

	UFUNCTION(BlueprintCallable)
	void WriteSaveGame(UMainSaveGame* SaveGame);

	UFUNCTION(BlueprintCallable)
	void SetNewPlayerName(FString newName);

	UFUNCTION(BlueprintCallable)
	UMainSaveGame* GetLoadedSaveGame();
	
private:
	UMainSaveGame* CreateInitialSaveGame();
	void BuildDataExampleStruct(TSharedPtr<FJsonObject> JsonObject, FJsonDataExampleStruct& DataExampleStruct);
};
