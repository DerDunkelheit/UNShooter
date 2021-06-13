// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/DialoguesSystem/DialogComponent.h"

#include "CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDialogComponent::UDialogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDialogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UDialogComponent::SendDialogues()
{
	if (Dialogues.Num() == 0) return;

	auto Instance = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (Instance != nullptr)
	{
		Instance->DialoguesManager()->SetupCurrentDialogues(Dialogues);
	}
}

void UDialogComponent::ShowNextDialog()
{
	auto Instance = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(Instance!= nullptr)
	{
		Instance->DialoguesManager()->ShowNextDialog();
	}
}
