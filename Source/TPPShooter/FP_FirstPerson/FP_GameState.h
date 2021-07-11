// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FP_GameState.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API AFP_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AFP_GameState();

	UFUNCTION(BlueprintCallable)
	int GetPlayerKillCount() const {return  PlayerKillCount; }
	
	UFUNCTION(BlueprintCallable)
	void IncreasePlayerKills();

private:
	int PlayerKillCount;
};
