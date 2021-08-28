// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPPShooter/Interfaces/Interactable.h"
#include "ChainExecutorActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSwitchState, bool, bEnable);

UCLASS()
class TPPSHOOTER_API AChainExecutorActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FSwitchState SwitchStateEvent;

public:
	// Sets default values for this actor's properties
	AChainExecutorActor();

	virtual void Interact_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bEnableFromStart;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool bEnable;
};
