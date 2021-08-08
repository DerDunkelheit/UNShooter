// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "TPPShooter/FP_FirstPerson/FP_FirstPersonCharacter.h"

#include "ObserverActor.generated.h"

UCLASS()
class TPPSHOOTER_API AObserverActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObserverActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UStaticMeshComponent* ActorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ObserverRadius = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ObserverAngle = 120;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bDebugMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bInstantSpot = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "!bInstantSpot"))
	float TimerToSpotPlayer = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AFP_FirstPersonCharacter* Player = nullptr;
	float PlayerVisibleTimer;

private:
	bool CanSeePlayer();
};