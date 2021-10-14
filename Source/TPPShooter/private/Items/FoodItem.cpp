// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/public/Items/FoodItem.h"

UFoodItem::UFoodItem()
{
	bStackable = true;
}

void UFoodItem::Use(AFP_FirstPersonCharacter* Character)
{
    Super::Use(Character);
	
    Character->GetHealthComponent()->RestoreHealth(HealthToIncrease);
	if(OwningInventory)
	{
		OwningInventory->RemoveItem(this);
	}
}
