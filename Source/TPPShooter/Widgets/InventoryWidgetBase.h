// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/InventoryComponent.h"
#include "InventoryWidgetBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseWidgetEvent);
UCLASS()
class TPPSHOOTER_API UInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ExposeOnSpawn="true"))
	UInventoryComponent* Inventory;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCloseWidgetEvent CloseWidgetEvent;
};
