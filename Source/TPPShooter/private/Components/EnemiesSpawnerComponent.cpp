// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemiesSpawnerComponent.h"

#include "TPPShooter/Actors/EnemiesRoomActor.h"

// Sets default values for this component's properties
UEnemiesSpawnerComponent::UEnemiesSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemiesSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Cast<AEnemiesRoomActor>(GetOwner())->PlayerEnteredEvent.AddDynamic(this, &UEnemiesSpawnerComponent::SpawnEnemy);
}


// Called every frame
void UEnemiesSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemiesSpawnerComponent::SpawnEnemy()
{
	auto RandomSpawningClass = PossibleEnemies[FMath::RandRange(0,PossibleEnemies.Num() - 1)];
	auto RandomPosition = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)]->GetActorLocation();
	
	auto Enemy = GetWorld()->SpawnActor<AActor>(RandomSpawningClass ,RandomPosition,FRotator::ZeroRotator);
	
	//Spawn enemy at random position.
	//Add health component.
	//Subscribe to health depleted event in order to open the door.
}

