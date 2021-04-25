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
		//TODO: we have to set it because pickup Actor is used cube as a default spawn object but cube is to big and we manually set in to 0.2 scale
		SetActorScale3D(FVector::OneVector);
		
		MeshComponent->SetStaticMesh(Item->PickupMesh);
	}
}

