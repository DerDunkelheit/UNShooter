#include "ExampleModule/Public/UI/CppExampleHUD.h"

AExampleHUD::AExampleHUD()
{
	
}

void AExampleHUD::BeginPlay()
{
	Super::BeginPlay();

	checkf(ExampleWidgetClass != nullptr, TEXT("ExampleWIdgetClass is nullptr, you probably should assign it manually"));

	ExampleWidget = CreateWidget<UCppExampleWidget>(GetWorld(), ExampleWidgetClass);
	if(ExampleWidget)
	{
		ExampleWidget->AddToViewport();
		//We can also assign events to ExampleWidget's variables here. For instance Get Player and bind to Damage taken event.
	}
}

void AExampleHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AExampleHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AExampleHUD::UpdateExampleText(int value)
{
	check(ExampleWidgetClass != nullptr);

	ExampleWidget->UpdateTextCount(value);
}

void AExampleHUD::ResetExampleText()
{
	check(ExampleWidgetClass != nullptr);
	
	ExampleWidget->ResetText();
}
