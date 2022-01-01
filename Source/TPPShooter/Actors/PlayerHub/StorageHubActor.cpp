// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerHub/StorageHubActor.h"
#include "Blueprint/UserWidget.h"
#include "NonUClasses/MacroUtils.h"

// Sets default values
AStorageHubActor::AStorageHubActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(StaticMeshComponent);
	InteractionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	InteractionArea->SetupAttachment(GetRootComponent());
	InteractionArea->ResetRelativeTransform();

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void AStorageHubActor::BeginPlay()
{
	Super::BeginPlay();

	TestDubug();

	TArray<TSharedPtr<FMyTestStruct>> someArray;
	for (int i = 0; i < 10; i ++)
	{
		someArray.Add(MakeShareable(new FMyTestStruct{test.testValue}));
	}

	for (auto a : someArray)
	{
		FString message = FString::FromInt(a->testValue);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
	}

	auto fdsfdsfd = someArray[0];
	fdsfdsfd->testValue = 2;

	for (auto a : someArray)
	{
		FString message = FString::FromInt(a->testValue);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
	}
}

void AStorageHubActor::OpenStorage()
{
	//Create widget

	if (IsValid(WidgetClass))
	{
		UInventoryWidgetBase* storageWidget = Cast<UInventoryWidgetBase>(CreateWidget(GetWorld(), WidgetClass));
		storageWidget->Inventory = InventoryComponent;
		storageWidget->AddToViewport();

		//Create Storage widget.
		//Bind to close widget, in order to hide it
	}
	else
	{
		//Handle error
	}
}

void AStorageHubActor::Interact_Implementation()
{
}

void AStorageHubActor::TestDubug()
{
	/*FString name = "Alex";
	int age = 19;
	FString message = FString::Printf(TEXT("Name: %s , age: %d"), *name, age);

	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Green, message);*/
}
