// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChainExecutorActor.h"
#include "GameFramework/Actor.h"
#include "ChainListenerActor.generated.h"

//TODO: we can create a chainListenerComponent, to avoid inheritance in some cases.
UCLASS()
class TPPSHOOTER_API AChainListenerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChainListenerActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	AChainExecutorActor* ExecutorActor;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnStateChanged(bool bEnable);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
