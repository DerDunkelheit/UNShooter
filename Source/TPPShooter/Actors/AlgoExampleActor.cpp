// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/AlgoExampleActor.h"

#include "Algo/Accumulate.h"
#include "Algo/AllOf.h"
#include "Algo/Compare.h"
#include "Algo/Copy.h"
#include "Algo/ForEach.h"
#include "Algo/MaxElement.h"
#include "Algo/Transform.h"

struct TestClass
{
	int health = 0;
};


// Sets default values
AAlgoExampleActor::AAlgoExampleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAlgoExampleActor::BeginPlay()
{
	Super::BeginPlay();

#ifdef TESTCASE
	//Linq select analog.
	TArray<int> intArray{5, 10, 12, 3};
	TArray<int> evenNumbers;
	Algo::CopyIf(intArray, evenNumbers, [](int x) { return x % 2 == 0; });
	for (int value : evenNumbers)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, FString::FromInt(value));
	}

	int sum = Algo::Accumulate(intArray,0);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::FromInt(sum));

	TArray<int> removeByPredicateExample{2,4,7,9};
	removeByPredicateExample.RemoveAll([](int x) { return x %2 == 0;});
	for (int value : removeByPredicateExample)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::FromInt(value));
	}

#endif
	
	TArray<TestClass> TestClasses;
	TArray<int> arrayOfHealth;
	for(int i = 0; i < 10; i ++)
	{
		TestClasses.Add(TestClass{i});
	}
	
	//Linq select example.
	Algo::Transform(TestClasses, arrayOfHealth, [](TestClass currentElement) { return currentElement.health; });

	for(auto health : arrayOfHealth)
	{
		auto test = FString::FromInt(health);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *test);
	}
	arrayOfHealth.Empty();
	
	Algo::TransformIf(TestClasses, arrayOfHealth, [](TestClass currentElement)
	{
		return currentElement.health % 2 ==0 ;
	},
    [](TestClass currentElement)
	{
    	return currentElement.health;
	});

	for(auto health : arrayOfHealth)
	{
		auto test = FString::FromInt(health);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *test);
	}
}

// Called every frame
void AAlgoExampleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
