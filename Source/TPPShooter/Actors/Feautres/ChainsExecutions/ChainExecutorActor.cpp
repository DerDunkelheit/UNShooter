// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/Feautres/ChainsExecutions/ChainExecutorActor.h"

// Sets default values
AChainExecutorActor::AChainExecutorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChainExecutorActor::BeginPlay()
{
	Super::BeginPlay();
	
	bEnable = bEnableFromStart;
	SwitchStateEvent.Broadcast(bEnable);
}

// Called every frame
void AChainExecutorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChainExecutorActor::Interact_Implementation()
{
	bEnable = !bEnable;
	SwitchStateEvent.Broadcast(bEnable);
}
