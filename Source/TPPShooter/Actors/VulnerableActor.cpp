// Fill out your copyright notice in the Description page of Project Settings.


#include "VulnerableActor.h"

// Sets default values
AVulnerableActor::AVulnerableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	DestroyEmmiterPosition = CreateDefaultSubobject<USceneComponent>(TEXT("EmissionPosition"));
	DestroyEmmiterPosition->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AVulnerableActor::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthDepleted.AddDynamic(this,&AVulnerableActor::SelfDestroy);
	
}
// Called every frame
void AVulnerableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVulnerableActor::SelfDestroy_Implementation()
{
	
}

