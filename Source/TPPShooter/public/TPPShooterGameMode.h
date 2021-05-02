// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPPShooterGameMode.generated.h"

UCLASS(minimalapi)
class ATPPShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPPShooterGameMode();

	virtual void BeginPlay() override;
};



