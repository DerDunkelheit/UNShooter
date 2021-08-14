// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/PowerUpActor.h"

#include "Kismet/GameplayStatics.h"
#include "TPPShooter/FP_FirstPerson/FP_FirstPersonCharacter.h"

// Sets default values
APowerUpActor::APowerUpActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractZone = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractZone"));
	VisualEffectActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("VisualEffectActor"));
	VisualEffectActor->ResetRelativeTransform();
}

// Called when the game starts or when spawned
void APowerUpActor::BeginPlay()
{
	Super::BeginPlay();

	InteractZone->OnComponentBeginOverlap.AddDynamic(this, &APowerUpActor::OnOverlapBegin);
}

// Called every frame
void APowerUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUpActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	//Probably we should get rid of interface, idk.
	if (Cast<AFP_FirstPersonCharacter>(OtherActor))
	{
		Execute_Interact(this);
	}
}

void APowerUpActor::PlayPickUpSound()
{
	if (PickUpSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickUpSound, GetActorLocation());
	}
}


void APowerUpActor::Interact_Implementation()
{
}
