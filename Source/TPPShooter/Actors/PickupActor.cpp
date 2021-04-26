// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::Interact_Implementation()
{ }

void APickupActor::SetItem(UItem* Item)
{
	CurrentItem = Item;

	if(Item->PickupMesh)
	{
		MeshComponent->SetStaticMesh(Item->PickupMesh);
	}
}

