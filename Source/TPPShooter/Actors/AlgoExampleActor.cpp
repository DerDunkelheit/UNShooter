// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/AlgoExampleActor.h"

#include "Algo/Accumulate.h"
#include "Algo/AllOf.h"
#include "Algo/Compare.h"
#include "Algo/Copy.h"
#include "Algo/Count.h"
#include "Algo/ForEach.h"
#include "Algo/MaxElement.h"
#include "Algo/Transform.h"


struct ExampleClass
{

	int a;
	
	~ExampleClass()
	{
		UE_LOG(LogTemp, Warning, TEXT("I was destroyed"));
	}
};

struct TestClass
{
	int health = 0;

	TSharedPtr<ExampleClass> e0;

	TArray<int> prefPositions;
};

struct A
{
	virtual ~A()
	{
		UE_LOG(LogTemp, Warning, TEXT("Destructor"));
	}
};

struct B : public A
{
	int test = 0;
};

// Sets default values
AAlgoExampleActor::AAlgoExampleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

FString AAlgoExampleActor::GetTestName()
{
	return ICppOnlyInterface::GetTestName();
}

// Called when the game starts or when spawned
void AAlgoExampleActor::BeginPlay()
{
	Super::BeginPlay();

	//FString myString = GetTestName();

	TSharedPtr<A> base = MakeShareable<A>(new A);
	TSharedPtr<B>  derived = MakeShareable<B>(new B);

	TestClass* a = new TestClass();
	{
		TSharedPtr<ExampleClass> e0;
		{
			//TUniquePtr<ExampleClass> a = MakeUnique<ExampleClass>();
			TSharedPtr<ExampleClass> myShared = MakeShareable<ExampleClass>(new ExampleClass);
			e0 = myShared;
			a->e0 = myShared;
		}
	}

	TArray<TestClass> myArray;
	TestClass first;
	first.prefPositions.Add(1);
	first.prefPositions.Add(2);
	first.prefPositions.Add(3);
	myArray.Add(first);

	TestClass second;
	second.prefPositions.Add(1);
	second.prefPositions.Add(2);
	
	second.prefPositions.Add(-1);
	myArray.Add(second);

	TestClass third;
	third.prefPositions.Add(1);
	third.prefPositions.Add(-1);
	third.prefPositions.Add(-1);
	myArray.Add(third);
	
	Algo::Sort(myArray, [](TestClass& a, TestClass& b)
	{
		int countA = Algo::CountIf(a.prefPositions, [](int currentPos)
			{
			  return currentPos != -1;
			});

		int countB = Algo::CountIf(b.prefPositions, [](int currentPos)
		{
			return currentPos != -1;
		});
		
		return countA < countB;
	});

	int fsdfd = 5;
	
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

	delete(a);
	a = nullptr;
	
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