// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FP_PlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPossessEvent, APawn*, NewPawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnPossessEvent);

UCLASS()
class TPPSHOOTER_API AFP_PlayerController : public APlayerController
{ 
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FPossessEvent PossessEvent;
	UPROPERTY(BlueprintAssignable)
	FUnPossessEvent UnPossessEvent;
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
