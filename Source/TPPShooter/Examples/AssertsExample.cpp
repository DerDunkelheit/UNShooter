// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Examples/AssertsExample.h"

// Sets default values
AAssertsExample::AAssertsExample()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAssertsExample::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAssertsExample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAssertsExample::CheckExample()
{
	//it throws an error and editor crashes. works only in Editor.
	//check(Number != 0);
	
	//check with error message,
	checkf(Number != 0, TEXT("Numer is 0, it's not allowed"))
}

void AAssertsExample::VerifyExample()
{
	//it throws an error and editor crashes. it works both in Editor and in Builds.
	verify(Number != 0);
}
