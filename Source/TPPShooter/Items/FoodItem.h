// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API UFoodItem : public UItem
{
	GENERATED_BODY()

public:

	UFoodItem();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
    float HealthToIncrease;

protected:
	virtual void Use(ATPPShooterCharacter* Character) override;
};
