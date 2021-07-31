// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"

#include "AbsorptionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPPSHOOTER_API UAbsorptionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<TSubclassOf<AActor>> AttractActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MagneticFieldRadius = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float AbsorptionSpeed = 1;

public:
	// Sets default values for this component's properties
	UAbsorptionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Setting")
	USphereComponent* MagnetSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	AActor* AbsorbedActor = nullptr;
	
	bool bIsAbsorbing;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
