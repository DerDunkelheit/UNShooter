// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemWidget.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/InventoryComponent.h"
#include "Structures/Line.h"
#include "Widgets/GameWidgetBase.h"
#include "InventoryGridWidget.generated.h"

UCLASS()
class TPPSHOOTER_API UInventoryGridWidget : public UGameWidgetBase
{
	GENERATED_BODY()

public:
	void InitializeGrid(UInventoryComponent* inventoryComponent, float tileSize);

	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UItemWidget> ItemWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UBorder* GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UCanvasPanel* GridCanvasPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TileSize;

protected:

	UPROPERTY(BlueprintReadOnly)
	TArray<FLine> Lines;

protected:
	virtual void NativeDestruct() override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	UFUNCTION(BlueprintCallable)
	void Refresh();
	
private:
	void CreateLineSegments();
};
