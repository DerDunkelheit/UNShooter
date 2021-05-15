// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"


#include "DrawDebugHelpers.h"
#include "TPPShooter/Interfaces/Interactable.h"
#include "TPPShooter/NonUClasses/GameDebuggerNew.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InteractRange = 100;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::TryInteract()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * InteractRange);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			IInteractable* Interactable = Cast<IInteractable>(Hit.GetActor());
			if (Interactable)
			{
				Interactable->Execute_Interact(Hit.GetActor());
			}
		}

		if (GameDebuggerNew::IsDebugInteractionEnable())
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Orange, false, 2);
		}
	}
}
