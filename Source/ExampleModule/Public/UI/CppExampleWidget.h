#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "CppExampleWidget.generated.h"

UCLASS()
class EXAMPLEMODULE_API UCppExampleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCppExampleWidget(const FObjectInitializer& ObjectInitializer);

	//BindWidget meta binds widget's elements inside canvas. You just need to drag widget's element to a canvas, in this case
	//textBlock and give it the same name, otherwise it won't be able to bind
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ExampleText;
	
public:

	virtual void NativeConstruct() override;
	
	void UpdateTextCount(int value);
	void ResetText();
 
	//should be place in base class for all gaming widgets.
	UWidgetAnimation* GetAnimationByName(FName animationName) const;

protected:
	UPROPERTY()
	TMap<FName, UWidgetAnimation*> AnimationsMap;

	//Like with BindWidget we can simply create animation with same name in UMG and it will find it.
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* ExampleFadeAnimation;

private:
	UPROPERTY()
	UWidgetAnimation* ExampleAnimationWithoutBindWidget;
};
