// Fill out your copyright notice in the Description page of Project Settings.

#define NAMEOF(name) #name

#include "TPPShooter/Actors/EnemyRoomActor.h"

#include "BehaviorTree/BTCompositeNode.h"

// Sets default values
AEnemyRoomActor::AEnemyRoomActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalDoorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Door Mesh"));
	SetRootComponent(SkeletalDoorMesh);
}

// Called when the game starts or when spawned
void AEnemyRoomActor::BeginPlay()
{
	Super::BeginPlay();

	verify(RoomActor != nullptr);
	RoomActor->PlayerEnteredEvent.AddDynamic(this, &AEnemyRoomActor::CloseDoor);
	RoomActor->RoomClearedEvent.AddDynamic(this, &AEnemyRoomActor::OnRoomCleared);

	//Example
	
	//RoomActor->TestDelegate.AddUFunction(this,NAMEOF(ExampleEventFunction));
	//RoomActor->TestEvent.AddUFunction(this,NAMEOF(ExampleEventFunction));

	//handles are used to store all binding so in future we can easily unbind them.
	//FDelegateHandle handle = RoomActor->TestDelegate.AddLambda([]() { });
	//RoomActor->TestDelegate.Remove(handle);
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