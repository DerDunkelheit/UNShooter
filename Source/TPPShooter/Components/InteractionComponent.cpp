// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"


#include "DrawDebugHelpers.h"
#include "TPPShooter/Interfaces/Interactable.h"

//TODO: create a class for console variables.
static int32 DebugInteractiveDrawing = 0;
FAutoConsoleVariableRef CVARDebugInteractiveDrawing(
    TEXT("Game.DebugInteraction"),
    DebugInteractiveDrawing,
    TEXT("Draw Debug Lines for Interaction"),
    ECVF_Cheat);

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

		if (DebugInteractiveDrawing > 0)
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Orange, false, 2);
		}
	}
}
