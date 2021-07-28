// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FloatingComponent.h"

// Sets default values for this component's properties
UFloatingComponent::UFloatingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloatingComponent::BeginPlay()
{
	Super::BeginPlay();

	Parent = GetOwner();
	if (Parent)
	{
		StartLocation = Parent->GetActorLocation();
		Parent->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	}
}


// Called every frame
void UFloatingComponent::TickComponent(float DeltaTime, ELevelTick TickType,    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float Time = GetWorld()->GetRealTimeSeconds();
	const float Sine = FMath::Sin(Time * SpeedMultiplier);

	if (Parent)
	{
		Parent->SetActorLocation(StartLocation + FloatRange * Sine);
	}
}
