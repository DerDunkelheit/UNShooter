// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RangeHighlightComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHighlightedEvent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TPPSHOOTER_API URangeHighlightComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URangeHighlightComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings");
	float TargetHighlightDuration = 3.0f;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnHighlightedEvent HighlightedEvent;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetProperties(UStaticMeshComponent* radiusSphereComponent, float increasingSpeed);
	UFUNCTION(BlueprintCallable)
	void TriggerHighlightExpand();

private:
	//TODO: maybe staticMeshComp isn't the best approach here.
	UPROPERTY()
	UStaticMeshComponent* RadiusSphereComponent;

	float ExpandingSpeed;
	float TimeElapsed;
	bool bLerpEnabled;

private:
	UFUNCTION()
	void OnRadiusSphereOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);
	UFUNCTION()
	void HandleHighlightFinish();
};
