// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EditorFunctionsExampleActor.h"


// Sets default values
AEditorFunctionsExampleActor::AEditorFunctionsExampleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
}

void AEditorFunctionsExampleActor::OnConstruction(const FTransform& Transform)
{
	//Blueprint's Construction Script equivalent.
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AEditorFunctionsExampleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEditorFunctionsExampleActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	//We can apply something by conditional
	const FName PropertyName(PropertyChangedEvent.Property->GetFName());
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AEditorFunctionsExampleActor, PostEditChangeBoolToggle))
	{
		int test = 6;
		//Some logic
	}
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
