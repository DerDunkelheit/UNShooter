// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPPShooter/Components/HealthComponent.h"

#include "VulnerableActor.generated.h"

UCLASS()
class TPPSHOOTER_API AVulnerableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVulnerableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Settings")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Settings")
	USceneComponent* DestroyEmmiterPosition;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Settings")
	UHealthComponent* HealthComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	UParticleSystem* DestroyParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	USoundWave* DestroySoundWave;
	
	UFUNCTION(BlueprintNativeEvent)
	void SelfDestroy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
