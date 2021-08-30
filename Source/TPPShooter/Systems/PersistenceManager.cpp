// Fill out your copyright notice in the Description page of Project Settings.

#include "TPPShooter/Systems/PersistenceManager.h"
#include "MainSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UPersistenceManager::Test()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Teeeest");
}

void UPersistenceManager::WriteSaveGame(UMainSaveGame* SaveGame)
{
	if(SaveGame != nullptr)
	{
		// Save the data immediately.
		if (UGameplayStatics::SaveGameToSlot(SaveGame, "TestSaveSlot", 0))
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "MainSaveGame Save succeeded");
		}
	}
}

UMainSaveGame* UPersistenceManager::GetLoadedSaveGame()
{
	if (UMainSaveGame* LoadedGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot("TestSaveSlot", 0)))
	{
		return LoadedGame;
	}

	return nullptr;
}

void UPersistenceManager::SetNewPlayerName(FString newName)
{
	UMainSaveGame* SaveGameInstance = GetLoadedSaveGame();
	if (SaveGameInstance == nullptr)
	{
		SaveGameInstance = CreateInitialSaveGame();
	}

	SaveGameInstance->PlayerName = newName;

	WriteSaveGame(SaveGameInstance);
}

UMainSaveGame* UPersistenceManager::CreateInitialSaveGame()
{
	auto SaveGame = Cast<UMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass()));
	if (UGameplayStatics::SaveGameToSlot(SaveGame, "TestSaveSlot", 0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, "Created Initial MainSaveGame object");
	}

	return SaveGame;
}