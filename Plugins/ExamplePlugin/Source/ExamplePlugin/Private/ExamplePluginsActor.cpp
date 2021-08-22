// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamplePluginsActor.h"

// Sets default values
AExamplePluginsActor::AExamplePluginsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AExamplePluginsActor::Test()
{
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Orange,TEXT("Test"));
}

// Called when the game starts or when spawned
void AExamplePluginsActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExamplePluginsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

