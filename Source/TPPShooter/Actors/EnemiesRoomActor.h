// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemiesRoomActor.generated.h"

//Blueprints will bind to this to update the UI.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerEnteredRoom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoomCleared);

//Delegates and Event example
DECLARE_MULTICAST_DELEGATE(FTestDelegate);
DECLARE_EVENT(AEnemiesRoomActor, FTestEvent);

UCLASS()
class TPPSHOOTER_API AEnemiesRoomActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemiesRoomActor();

	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnPlayerEnteredRoom PlayerEnteredEvent;

	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnRoomCleared RoomClearedEvent;

	//Example
	FTestDelegate TestDelegate;
    FTestEvent TestEvent;
	//

	TArray<int> testArray;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UBoxComponent* RoomEnterTrigger;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable)
	void PrintArrayValues();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
