// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ZoomComponent.h"

// Sets default values for this component's properties
UZoomComponent::UZoomComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ZoomValue = 65;
	ZoomInterpSpeed = 20;
}


// Called when the game starts
void UZoomComponent::BeginPlay()
{
	Super::BeginPlay();

	Camera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	if(Camera)
	{
		DefaultFOV = Camera->FieldOfView;
	}
}

// Called every frame
void UZoomComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float TargetFOV = bWantsZoom ? ZoomValue : DefaultFOV;
	float NewFOV = FMath::FInterpTo(Camera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
	Camera->SetFieldOfView(NewFOV);
}

void UZoomComponent::StartZoom()
{
	bWantsZoom = true;
}

void UZoomComponent::EndZoom()
{
	bWantsZoom = false;
}

