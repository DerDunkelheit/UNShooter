// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LootableActor.h"
#include "Components/InventoryComponent.h"

// Sets default values
ALootableActor::ALootableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMeshComponent);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	DataTableLootComponent = CreateDefaultSubobject<UDataTableLootComponent>(TEXT("LootComponent"));
}

// Called when the game starts or when spawned
void ALootableActor::BeginPlay()
{
	Super::BeginPlay();

	GenerateLoot();
}

void ALootableActor::Interact_Implementation()
{ }

void ALootableActor::GenerateLoot()
{
	int lootCount = FMath::RandRange(1, 4);
	TArray<UItem*> items = DataTableLootComponent->GenerateLoot(lootCount);

	InventoryComponent->AddItems(items);
}
