// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/InventoryComponent.h"
#include "Widgets/GameWidgetBase.h"
#include "InventoryGridWidget.generated.h"

//Class for holding positions for drawing grid's segments.
USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D End;

	FLine() = default;

	FLine(FVector2D start, FVector2D end)
	{
		Start = start;
		End = end;
	}
};

UCLASS()
class TPPSHOOTER_API UInventoryGridWidget : public UGameWidgetBase
{
	GENERATED_BODY()

public:
	void InitializeGrid(UInventoryComponent* inventoryComponent, float tileSize);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UBorder* GridBorder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TileSize;

protected:

	UPROPERTY(BlueprintReadOnly)
	TArray<FLine> Lines;
	
private:
	void CreateLineSegments();
};
