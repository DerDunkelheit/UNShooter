// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExampleSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API UExampleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	//Because it's a UGameInstanceSubsystem's subclass, it Initializes when GameInstance Initializes, same with Deinitializing
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	int testValue = 0;
};
