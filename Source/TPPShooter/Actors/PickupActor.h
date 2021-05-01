// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPPShooter/Interfaces/Interactable.h"
#include "TPPShooter/public/Items/Item.h"

#include "PickupActor.generated.h"

UCLASS()
class TPPSHOOTER_API APickupActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Settings")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Settings")
	class UItem* CurrentItem;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    virtual void Interact_Implementation() override;

	void SetItem(UItem* Item);
};
