// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ExampleSubsystem.h"

void UExampleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	testValue = 10;
}

void UExampleSubsystem::Deinitialize()
{
	Super::Deinitialize();

	
}
