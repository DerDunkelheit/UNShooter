// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/Feautres/RemoteControl/RemoteControllerActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ARemoteControllerActor::ARemoteControllerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);
}

// Called when the game starts or when spawned
void ARemoteControllerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARemoteControllerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARemoteControllerActor::SetLastControlledPawn(ARemotelyControlledPawn* LastPawn)
{
	LastControlledPawn = LastPawn;
}

ARemotelyControlledPawn* ARemoteControllerActor::GetControlledPawnByIndex(int Index)
{
	if (Index >= ControlledPawns.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Index %d isn't valid, Array length: %d"), Index, ControlledPawns.Num());
		return nullptr;
	}

	return ControlledPawns[Index];
}

void ARemoteControllerActor::Interact_Implementation()
{
}
