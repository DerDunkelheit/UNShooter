// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TPPShooter/Enums/AmmoTypeEnum.h"
#include "TPPShooter/public/Items/Item.h"

#include "AmmoItem.generated.h"

UCLASS()
class TPPSHOOTER_API UAmmoItem : public UItem
{
	GENERATED_BODY()

public:
	UAmmoItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo class setting")
	AmmoTypeEnum AmmoType;
};