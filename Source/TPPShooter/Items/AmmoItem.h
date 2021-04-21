// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TPPShooter/Enums/AmmoTypeEnum.h"
#include "TPPShooter/Items/Item.h"

#include "AmmoItem.generated.h"

UCLASS()
//TODO: remove click text in tooltip field.
class TPPSHOOTER_API UAmmoItem : public UItem
{
	GENERATED_BODY()

public:
	UAmmoItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo class setting")
	AmmoTypeEnum AmmoType;
};
