// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamplePluginsComponent.h"

// Sets default values for this component's properties
UExamplePluginsComponent::UExamplePluginsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExamplePluginsComponent::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Orange,TEXT("Hello from plugin!"));
}


// Called every frame
void UExamplePluginsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

