// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateTowardActor.generated.h"

UCLASS()
class TPPSHOOTER_API ARotateTowardActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARotateTowardActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USceneComponent* RotationPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RotationMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	AActor* ActorToRotate = nullptr;
};
