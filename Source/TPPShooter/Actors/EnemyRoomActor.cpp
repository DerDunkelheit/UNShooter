// Fill out your copyright notice in the Description page of Project Settings.

#define NAMEOF(name) #name

#include "TPPShooter/Actors/EnemyRoomActor.h"

#include "BehaviorTree/BTCompositeNode.h"

// Sets default values
AEnemyRoomActor::AEnemyRoomActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	SetRootComponent(DoorMesh);
}

// Called when the game starts or when spawned
void AEnemyRoomActor::BeginPlay()
{
	Super::BeginPlay();

	verify(RoomActor != nullptr);

	SetActorEnableCollision(false);

	RoomActor->PlayerEnteredEvent.AddDynamic(this, &AEnemyRoomActor::CloseDoor);

	//Example
	
	RoomActor->TestDelegate.AddUFunction(this,NAMEOF(ExampleEventFunction));
	RoomActor->TestEvent.AddUFunction(this,NAMEOF(ExampleEventFunction));
}

// Called every frame
void AEnemyRoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyRoomActor::FillArrayWithRandom(TArray<int>& Array)
{
	for (int i = 0; i != 10; i++)
	{
		Array.Add(FMath::RandRange(0, 100));
	}
}

void AEnemyRoomActor::CloseDoor()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	//this->AddInstanceComponent(NewObject<UHealthComponent>());
	FillArrayWithRandom(RoomActor->testArray);
}

//Example

void AEnemyRoomActor::ExampleEventFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, "From test function");
}

void AEnemyRoomActor::RawExampleFunction()
{
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Cyan, TEXT("From raw function"));
}
