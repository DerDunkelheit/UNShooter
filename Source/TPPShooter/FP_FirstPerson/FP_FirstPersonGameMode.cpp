// Copyright Epic Games, Inc. All Rights Reserved.

#include "FP_FirstPersonGameMode.h"
#include "FP_FirstPersonHUD.h"
#include "TPPShooter/FP_FirstPerson/FP_GameState.h"
#include "Kismet/GameplayStatics.h"

AFP_FirstPersonGameMode::AFP_FirstPersonGameMode()
{
	// Use our custom HUD class
	HUDClass = AFP_FirstPersonHUD::StaticClass();

	PointToWin = 5;
}

void AFP_FirstPersonGameMode::OnTargetDied()
{
	AFP_GameState* CustomGameState = Cast<AFP_GameState>(GameState);
	if (CustomGameState != nullptr)
	{
		CustomGameState->IncreasePlayerKills();

		if (CustomGameState->GetPlayerKillCount() >= PointToWin)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "You won");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow,
			                                 FString::Printf(
				                                 TEXT("Your score: %d"), CustomGameState->GetPlayerKillCount()));
		}
	}
}
