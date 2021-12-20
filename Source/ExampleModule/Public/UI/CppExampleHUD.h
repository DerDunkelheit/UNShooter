#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "ExampleModule/Public/UI/CppExampleWidget.h"

#include "CppExampleHUD.generated.h"

UCLASS()
class AExampleHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UUserWidget> ExampleWidgetClass;
	
public:

	AExampleHUD();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void DrawHUD() override;

	UFUNCTION()
	void UpdateExampleText(int value);

	UFUNCTION()
	void ResetExampleText();

private:
	UPROPERTY()
	UCppExampleWidget* ExampleWidget;
};
