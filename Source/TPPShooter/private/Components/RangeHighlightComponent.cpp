// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/RangeHighlightComponent.h"
#include "Interfaces/HighlightInterface.h"

// Sets default values for this component's properties
URangeHighlightComponent::URangeHighlightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URangeHighlightComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
}

// Called every frame
void URangeHighlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bLerpEnabled)
	{
		if(RadiusSphereComponent == nullptr)
		{
			//log into file????
			UE_LOG(LogTemp, Warning, TEXT("Attempt to use RangeHighlightComponent with unassignent SphereComponent"))
			bLerpEnabled = false;
			return;
		}
		
		if (TimeElapsed < ExpandingSpeed)
		{
			RadiusSphereComponent->SetWorldScale3D(FMath::Lerp(FVector::OneVector, FVector::OneVector * 20, TimeElapsed / ExpandingSpeed));
			TimeElapsed += DeltaTime;
		}
		else
		{
			HandleHighlightFinish();
		}
	}
}

void URangeHighlightComponent::OnRadiusSphereOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UHighlightInterface::StaticClass()))
	{
		IHighlightInterface::Execute_Highlight(OtherActor, TargetHighlightDuration);
	}
}

void URangeHighlightComponent::HandleHighlightFinish()
{
	bLerpEnabled = false;
	TimeElapsed = 0;
	RadiusSphereComponent->SetWorldScale3D(FVector::OneVector);
	SetComponentTickEnabled(false);

	HighlightedEvent.Broadcast();
}

void URangeHighlightComponent::SetProperties(UStaticMeshComponent* radiusSphereComponent, float increasingSpeed)
{
	RadiusSphereComponent = radiusSphereComponent;
	ExpandingSpeed = increasingSpeed;

	RadiusSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &URangeHighlightComponent::OnRadiusSphereOverlapped);
}

void URangeHighlightComponent::TriggerHighlightExpand()
{
	SetComponentTickEnabled(true);
	bLerpEnabled = true;
}