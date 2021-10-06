// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPPShooter/Actors/Feautres/RemoteControl/RemotelyControlledPawn.h"
#include "RemotelyControlledCamera.generated.h"

/**
 * 
 */
UCLASS()
class TPPSHOOTER_API ARemotelyControlledCamera : public ARemotelyControlledPawn
{
	GENERATED_BODY()
public:
	ARemotelyControlledCamera();


public:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UStaticMeshComponent* StaticMeshComponent;

private:
	void SelectLeftCamera();
	void SelectRightCamera();
};
