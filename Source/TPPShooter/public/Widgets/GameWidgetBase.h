// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API UGameWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UWidgetAnimation* GetAnimationByName(FName animationName) const;

protected:
	UPROPERTY()
	TMap<FName, UWidgetAnimation*> AnimationsMap;
};
