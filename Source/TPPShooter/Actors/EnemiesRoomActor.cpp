// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/EnemiesRoomActor.h"

// Sets default values
AEnemiesRoomActor::AEnemiesRoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoomEnterTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Room enter trigger"));
}

// Called when the game starts or when spawned
void AEnemiesRoomActor::BeginPlay()
{
	Super::BeginPlay();
	
	RoomEnterTrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemiesRoomActor::OnEnterOverlap);
}

void AEnemiesRoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemiesRoomActor::OnEnterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,4,FColor::Orange,"Player entered the room");
	PlayerEnteredEvent.Broadcast();
	TestDelegate.Broadcast();
	TestEvent.Broadcast();
}

//Example

void AEnemiesRoomActor::PrintArrayValues()
{
    if(testArray.Num() == 0)
    {
    	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("Empty array"));
    }
	
	for (int value : testArray)
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green,FString::FromInt(value));
	}
}
