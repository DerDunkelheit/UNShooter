// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

//TODO: create max item stacks
//TODO: create items division into parts

class UInventoryComponent;
class AFP_FirstPersonCharacter;

UCLASS(BlueprintType, Blueprintable, EditInlineNew , DefaultToInstanced)
class TPPSHOOTER_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();

	UPROPERTY(Transient)
	class UWorld* World;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item | General")
	bool bCanBeUsed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | General", meta = (EditCondition = "bCanBeUsed"))
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | General")
	UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | General")
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | General")
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | General", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | General", meta = (ClampMin = 0.0))
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | General")
	bool bCanBeRemoved = true;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | General")
	bool bStackable = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | General", meta = (EditCondition = "bStackable"))
	int Quantity;

	// --- Grid inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Grid", meta=(ExposeOnSpawn = "true"))
	FIntPoint Dimensions;

	UPROPERTY(BlueprintReadOnly)
	bool bRotated = false;

	//ExposeOnSpawn????
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item | Grid")
	UMaterialInterface* GridIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item | Grid")
	UMaterialInterface* GridIconRotated;
	// ---

	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetIcon();
	
	UPROPERTY()
	UInventoryComponent* OwningInventory;

	virtual class UWorld* GetWorld() const { return World; }
	virtual void Use(AFP_FirstPersonCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(AFP_FirstPersonCharacter* Character);

	FIntPoint GetDimensions();
};
