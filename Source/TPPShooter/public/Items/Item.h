// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TPPShooter/TPPShooterCharacter.h"
#include "UObject/NoExportTypes.h"
#include "Components/InventoryComponent.h"
#include "Item.generated.h"

//TODO: create max item stacks
//TODO: create items division into parts

UCLASS(BlueprintType, Blueprintable, EditInlineNew , DefaultToInstanced)
class TPPSHOOTER_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();

	UPROPERTY(Transient)
	class UWorld* World;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	bool bCanBeUsed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (EditCondition = "bCanBeUsed"))
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bCanBeRemoved = true;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bStackable = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (EditCondition = "bStackable"))
	int Quantity;
	
	UPROPERTY()
	UInventoryComponent* OwningInventory;

	virtual class UWorld* GetWorld() const { return World; }
	virtual void Use(ATPPShooterCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(ATPPShooterCharacter* Character);
};
