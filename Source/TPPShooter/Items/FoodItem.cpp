// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"

UFoodItem::UFoodItem()
{
	bStackable = true;
}

void UFoodItem::Use(ATPPShooterCharacter* Character)
{
    Super::Use(Character);
	
    Character->HealthComponent->RestoreHealth(HealthToIncrease);
	if(OwningInventory)
	{
		OwningInventory->RemoveItem(this);
	}
}
