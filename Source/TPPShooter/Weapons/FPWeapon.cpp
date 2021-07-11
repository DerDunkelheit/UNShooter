// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Weapons/FPWeapon.h"

void AFPWeapon::Fire()
{
	Super::Fire();

	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"Override");
}
