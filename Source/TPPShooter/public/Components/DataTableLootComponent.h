// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Items/Item.h"
#include "DataTableLootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPPSHOOTER_API UDataTableLootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDataTableLootComponent();

	UFUNCTION(BlueprintCallable)
	TArray<UItem*> GenerateLoot(int count);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	UDataTable* LootTable;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Test();
};
