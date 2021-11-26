// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DataTableLootComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "LootableActor.generated.h"

class InventoryComponent;

UCLASS()
class TPPSHOOTER_API ALootableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootableActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UInventoryComponent* InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UDataTableLootComponent* DataTableLootComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;

private:
	void GenerateLoot();
};
