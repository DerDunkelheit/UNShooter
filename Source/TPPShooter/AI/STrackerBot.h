// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/HealthComponent.h"

#include "STrackerBot.generated.h"

UCLASS()
class TPPSHOOTER_API ASTrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTrackerBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USphereComponent* PlayerDetectArea;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	URadialForceComponent* RadialForceComponent;

	FVector GetNextPathPoint();

	FVector NextPathPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MovementForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bUseVelocityChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float RequiredDistanceToTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ExplosionRadiusOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ExplosionDamage;

	UFUNCTION(BlueprintImplementableEvent)
	void DieEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
