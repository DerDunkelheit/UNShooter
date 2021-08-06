// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EnemiesRoomActor.h"
#include "GameFramework/Actor.h"
#include "EnemyRoomActor.generated.h"

UCLASS()
class TPPSHOOTER_API AEnemyRoomActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyRoomActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Settings")
	AEnemiesRoomActor* RoomActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UStaticMeshComponent* DoorMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FillArrayWithRandom(TArray<int>& Array);

private:
	UFUNCTION()
	void CloseDoor();

	//Example
	
	UFUNCTION()
	void ExampleEventFunction();

	void RawExampleFunction();
};
