// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemiesSpawnerComponent.generated.h"

class AEnemiesRoomActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPPSHOOTER_API UEnemiesSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemiesSpawnerComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TArray<AActor*> SpawnPoints;

	//We can also create a class for spawning actor.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	TArray<TSubclassOf<AActor>> PossibleEnemies;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AEnemiesRoomActor* Owner = nullptr;
	
private:
	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void OnEnemyDied();

	void AddHealthComponentToEnemy(AActor* Enemy);
};
