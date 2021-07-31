// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbsorptionComponent.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UAbsorptionComponent::UAbsorptionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MagnetSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	MagnetSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	MagnetSphere->SetupAttachment(this);
	MagnetSphere->SetRelativeLocation(FVector::ZeroVector);
	MagnetSphere->SetSphereRadius(MagneticFieldRadius);
}


// Called when the game starts
void UAbsorptionComponent::BeginPlay()
{
	Super::BeginPlay();

	MagnetSphere->OnComponentBeginOverlap.AddDynamic(this, &UAbsorptionComponent::OnOverlapEnter);
	MagnetSphere->OnComponentEndOverlap.AddDynamic(this, &UAbsorptionComponent::OnEndOverlap);
}

// Called every frame
void UAbsorptionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bIsAbsorbing && AbsorbedActor)
	{
		AbsorbedActor->SetActorLocation(FMath::VInterpTo(AbsorbedActor->GetActorLocation(),this->GetComponentLocation(), DeltaTime, AbsorptionSpeed));
	}

	DrawDebugSphere(GetWorld(),this->GetComponentLocation(),MagneticFieldRadius,25,FColor::Orange);
}

void UAbsorptionComponent::OnOverlapEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AttractActors.Contains(OtherActor->GetClass()))
	{
		AbsorbedActor = OtherActor;
		bIsAbsorbing = true;
	}
}

void UAbsorptionComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(AbsorbedActor != nullptr && AbsorbedActor == OtherActor)
	{
		AbsorbedActor = nullptr;
		bIsAbsorbing = false;
	}
}

void UAbsorptionComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	MagnetSphere->DestroyComponent();
}

void UAbsorptionComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Displays new sphere radius when we change it in editor.
	MagnetSphere->SetSphereRadius(MagneticFieldRadius);
}

