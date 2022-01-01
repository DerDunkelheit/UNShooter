// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Items/Item.h"
#include "Widgets/GameWidgetBase.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API UItemWidget : public UGameWidgetBase
{
	GENERATED_BODY()

public:
	//We have to use it, because we want to achieve similar behavior to ExposeOnSpawn in BP. maybe it's not the best solution. TODO: make research.
	void SetInitialProperties(float tileSize, UItem* item);

protected:
	UPROPERTY(BlueprintReadOnly)
	UItem* Item;
	
	UPROPERTY(BlueprintReadOnly)
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	USizeBox* BackgroundSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UImage* ItemImage;
};
