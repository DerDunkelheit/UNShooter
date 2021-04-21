// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AmmoTypeEnum.generated.h"

UENUM(BlueprintType)
enum class AmmoTypeEnum : uint8
{
	Ammo556 = 0 UMETA(DisplayName = "5.56 Ammo"),
	TestAmmo = 1 UMETA(DisplayName = "Test field"),
};
