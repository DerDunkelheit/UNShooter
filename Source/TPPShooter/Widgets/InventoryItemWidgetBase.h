// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/Item.h"
#include "InventoryItemWidgetBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemRemovedEvent, UItem*, RemovedItem);

UCLASS()
class TPPSHOOTER_API UInventoryItemWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FItemRemovedEvent ItemRemovedEvent;
};
