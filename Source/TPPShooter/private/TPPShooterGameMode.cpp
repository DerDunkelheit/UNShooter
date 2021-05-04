// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPPShooter/public/TPPShooterGameMode.h"

#include "LogSystem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

ATPPShooterGameMode::ATPPShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void ATPPShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	int test = 5;
	ULogSystem::Message(FString::Printf(TEXT("value: %d"), test), FColor::Orange);
}
