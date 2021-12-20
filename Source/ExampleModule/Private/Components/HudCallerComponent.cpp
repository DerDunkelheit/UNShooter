// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HudCallerComponent.h"

#include "Kismet/GameplayStatics.h"
#include "UI/CppExampleHUD.h"


// Sets default values for this component's properties
UHudCallerComponent::UHudCallerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UHudCallerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHudCallerComponent::UpdateExampleText(int value)
{
	AExampleHUD* exampleHud = Cast<AExampleHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	if(exampleHud)
	{
		ExecutionCount++;
		exampleHud->UpdateExampleText(ExecutionCount);
	}
}

void UHudCallerComponent::ResetExampleText()
{
	AExampleHUD* exampleHud = Cast<AExampleHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	if(exampleHud)
	{
		ExecutionCount = 0;
		exampleHud->ResetExampleText();
	}
}

