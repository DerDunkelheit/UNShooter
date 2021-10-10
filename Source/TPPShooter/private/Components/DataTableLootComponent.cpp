// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DataTableLootComponent.h"

#include "CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDataTableLootComponent::UDataTableLootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UDataTableLootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UDataTableLootComponent::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Some text"));
}

TArray<UItem*> UDataTableLootComponent::GenerateLoot(int count)
{
	auto* gameInstance = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto* parser = gameInstance->GetDataTablesParser();
	TArray<UItem*> lootNames = parser->GetLoots(LootTable, count);
	return lootNames;
}
