#include "ExampleModule/Public/UI/CppExampleWidget.h"
#include "Blueprint/WidgetTree.h"
#include "TPPShooter/GameplayUtilities/GameUtils.h"

UCppExampleWidget::UCppExampleWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UCppExampleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameUtils::StoreWidgetAnimations(this, AnimationsMap);

	//we can use that approach if we don't want to use BindWidget meta. 
	ExampleAnimationWithoutBindWidget = GetAnimationByName("SomeAnimation");

	//Bind to delegates here.
}

void UCppExampleWidget::UpdateTextCount(int value)
{
	if(ExampleText)
	{
		if (ExampleText->Visibility == ESlateVisibility::Hidden)
		{
			ExampleText->SetVisibility(ESlateVisibility::Visible);
		}
		
		ExampleText->SetText(FText::FromString("value: " + FString::FromInt(value)));
	}
}

void UCppExampleWidget::ResetText()
{
	if(ExampleFadeAnimation)
	{
		PlayAnimation(ExampleFadeAnimation,0, 1);
	}
}

UWidgetAnimation* UCppExampleWidget::GetAnimationByName(FName animationName) const
{
	UWidgetAnimation* const* widgetAnimation = AnimationsMap.Find(animationName);
	if(widgetAnimation != nullptr)
	{
		return *widgetAnimation;
	}

	return nullptr;
}
