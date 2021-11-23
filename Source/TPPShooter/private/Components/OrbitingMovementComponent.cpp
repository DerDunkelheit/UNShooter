// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OrbitingMovementComponent.h"

// Sets default values for this component's properties
UOrbitingMovementComponent::UOrbitingMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RotateToFaceOutwards = true;
	RotationSpeed = 5;
	OrbitingDistance = 100;
	CurrentValue = 0;
}


// Called when the game starts
void UOrbitingMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UOrbitingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float currentValuesInRadians = FMath::DegreesToRadians<float>(CurrentValue);
	SetRelativeLocation(FVector(OrbitingDistance * FMath::Cos(currentValuesInRadians),
	                            OrbitingDistance * FMath::Sin(currentValuesInRadians), GetRelativeLocation().Z));
	if(RotateToFaceOutwards)
	{
		FVector lookDir = (GetRelativeLocation()).GetSafeNormal();
		FRotator lookAtRot = lookDir.Rotation();
		SetRelativeRotation(lookAtRot);
	}

	CurrentValue = FMath::Fmod(CurrentValue + (RotationSpeed * DeltaTime), 360);
}

