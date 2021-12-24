// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/GameWidgetBase.h"

#include "GameplayUtilities/GameUtils.h"

void UGameWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	GameUtils::StoreWidgetAnimations(this, AnimationsMap);
	
	//Bind to delegates here.
}

UWidgetAnimation* UGameWidgetBase::GetAnimationByName(FName animationName) const
{
	UWidgetAnimation* const* widgetAnimation = AnimationsMap.Find(animationName);
	if(widgetAnimation != nullptr)
	{
		return *widgetAnimation;
	}

	return nullptr;
}