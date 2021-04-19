// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TPPShooter/TPPShooterCharacter.h"
#include "UObject/NoExportTypes.h"
#include "TPPShooter/Components/InventoryComponent.h"
#include "Item.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew , DefaultToInstanced)
class TPPSHOOTER_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();

	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
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
	class UInventoryComponent* OwningInventory;

	virtual class UWorld* GetWorld() const { return World; }
	virtual void Use(ATPPShooterCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(ATPPShooterCharacter* Character);
};
