// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/Feautres/ChainsExecutions/ChainListenerActor.h"

// Sets default values
AChainListenerActor::AChainListenerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChainListenerActor::BeginPlay()
{
	Super::BeginPlay();

	verifyf(ExecutorActor != nullptr, TEXT("ExecutorActor wasn't assigned"))

	ExecutorActor->SwitchStateEvent.AddDynamic(this,&AChainListenerActor::OnStateChanged);
}

// Called every frame
void AChainListenerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

