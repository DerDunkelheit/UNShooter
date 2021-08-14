// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/TeleportPointActor.h"

#include "TPPShooter/FP_FirstPerson/FP_FirstPersonCharacter.h"

// Sets default values
ATeleportPointActor::ATeleportPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	SetRootComponent(DefaultRootComponent);
	TeleportTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Teleport Trigger"));
	EnableTeleportTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Enable Teleport Trigger"));
	EnableTeleportTrigger->SetupAttachment(DefaultRootComponent);
	EnableTeleportTrigger->ResetRelativeTransform();
}

// Called when the game starts or when spawned
void ATeleportPointActor::BeginPlay()
{
	Super::BeginPlay();

	TeleportTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATeleportPointActor::OnTeleportTriggerOverlap);
	EnableTeleportTrigger->OnComponentEndOverlap.AddDynamic(this, &ATeleportPointActor::OnEnableTeleportEndOverlap);
}

void ATeleportPointActor::DisableTeleportBoxArea()
{
	TeleportTrigger->SetGenerateOverlapEvents(false);
}

void ATeleportPointActor::OnEnableTeleportEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                     AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TeleportTrigger->SetGenerateOverlapEvents(true);
}

void ATeleportPointActor::OnTeleportTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(TeleportToPoint == nullptr) return;
	
	auto Player = Cast<AFP_FirstPersonCharacter>(OtherActor);
	if(Player != nullptr)
	{
		TeleportToPoint->DisableTeleportBoxArea();
		Player->SetActorLocation(TeleportToPoint->GetActorLocation());
	}
}