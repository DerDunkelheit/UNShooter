// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemiesSpawnerComponent.h"

#include "Components/HealthComponent.h"
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

	Owner = Cast<AEnemiesRoomActor>(GetOwner());
	Owner->PlayerEnteredEvent.AddDynamic(this, &UEnemiesSpawnerComponent::SpawnEnemy);
}


// Called every frame
void UEnemiesSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemiesSpawnerComponent::SpawnEnemy()
{
	auto RandomSpawningClass = PossibleEnemies[FMath::RandRange(0, PossibleEnemies.Num() - 1)];
	auto SpawnPoint = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];

	auto Enemy = GetWorld()->SpawnActor<AActor>(RandomSpawningClass, SpawnPoint->GetActorLocation(),SpawnPoint->GetActorRotation());
	Owner->IncreaseEnemiesNumber();
	UHealthComponent* HealthComponent = Enemy->FindComponentByClass<UHealthComponent>();

	if (HealthComponent == nullptr)
	{
		AddHealthComponentToEnemy(Enemy);
	}
	else
	{
		HealthComponent->OnHealthDepleted.AddDynamic(this, &UEnemiesSpawnerComponent::OnEnemyDied);
	}
}

void UEnemiesSpawnerComponent::AddHealthComponentToEnemy(AActor* Enemy)
{
	UHealthComponent* HealthComponent = NewObject<UHealthComponent>(Enemy);
	HealthComponent->RegisterComponent();
	HealthComponent->OnHealthDepleted.AddDynamic(this, &UEnemiesSpawnerComponent::OnEnemyDied);
	HealthComponent->BindDefaultOnHealthDepletedLogic();
}

void UEnemiesSpawnerComponent::OnEnemyDied()
{
	Owner->DecreaseEnemiesNumber();
}
