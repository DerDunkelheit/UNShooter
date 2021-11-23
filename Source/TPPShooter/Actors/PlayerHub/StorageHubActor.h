// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/InventoryComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Widgets/InventoryWidgetBase.h"
#include "StorageHubActor.generated.h"

USTRUCT(BlueprintType)
struct FMyTestStruct
{
   GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Test")
	int testValue;
};

UCLASS()
class TPPSHOOTER_API AStorageHubActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorageHubActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UBoxComponent* InteractionArea;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<UInventoryWidgetBase> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	FMyTestStruct test;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OpenStorage();

public:
	virtual void Interact_Implementation() override;


	//For testing, remove later
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	FStringClassReference ClassReferenceTest;

	void TestDubug();
};
