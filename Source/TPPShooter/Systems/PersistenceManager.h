// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainSaveGame.h"
#include "UObject/NoExportTypes.h"
#include "PersistenceManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TPPSHOOTER_API UPersistenceManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Test();

	UFUNCTION(BlueprintCallable)
	void WriteSaveGame(UMainSaveGame* SaveGame);

	UFUNCTION(BlueprintCallable)
	void SetNewPlayerName(FString newName);

	UFUNCTION(BlueprintCallable)
	UMainSaveGame* GetLoadedSaveGame();
	
private:
	UMainSaveGame* CreateInitialSaveGame();
};
