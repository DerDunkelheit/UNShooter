// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TeleportPointActor.generated.h"

UCLASS()
class TPPSHOOTER_API ATeleportPointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportPointActor();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultRootComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBoxComponent* TeleportTrigger;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBoxComponent* EnableTeleportTrigger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	ATeleportPointActor* TeleportToPoint = nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTeleportTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnEnableTeleportEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	void DisableTeleportBoxArea();
};
