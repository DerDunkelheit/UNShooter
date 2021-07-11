// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPPShooter/Weapons/Weapon.h"
#include "FPWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API AFPWeapon : public AWeapon
{
	GENERATED_BODY()


protected:
	virtual void Fire() override;
};
