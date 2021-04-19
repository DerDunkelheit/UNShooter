// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPPShooterGameMode.h"
#include "TPPShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPPShooterGameMode::ATPPShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
