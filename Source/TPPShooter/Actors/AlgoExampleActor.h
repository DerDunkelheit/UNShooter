// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleModule/Public/Interfaces/CppOnlyInterface.h"
#include "AlgoExampleActor.generated.h"

UCLASS()
class TPPSHOOTER_API AAlgoExampleActor : public AActor , public ICppOnlyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlgoExampleActor();

	virtual FString GetTestName() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
