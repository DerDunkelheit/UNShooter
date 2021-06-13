// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialoguesManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogStartedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogEndedEvent);

UCLASS(BlueprintType, Blueprintable)
class TPPSHOOTER_API UDialoguesManager : public UObject
{
	GENERATED_BODY()

public:
	void SetupCurrentDialogues(TArray<FString> Dialogues);
	
	UFUNCTION(BlueprintCallable)
	void ShowNextDialog();

	UFUNCTION(BlueprintCallable)
	void SetupDefaultDialogues();

	UFUNCTION(BlueprintCallable)
	void ClearDialogues();

	UFUNCTION(BlueprintCallable)
	bool HasDialog() const {return !CurrentDialogues.IsEmpty();}

	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FDialogStartedEvent DialogStartedEvent;
	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FDialogEndedEvent DialogEndedEvent;

private:
	TQueue<FString> CurrentDialogues;
};
