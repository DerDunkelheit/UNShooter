// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneCaptureComponent2D.h"
#include "RemotelyControlledPawn.generated.h"

UCLASS()
class TPPSHOOTER_API ARemotelyControlledPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARemotelyControlledPawn();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	USceneCaptureComponent2D* SceneCaptureComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void AddControllerYawInput(float Value) override;
	virtual void AddControllerPitchInput(float Value) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
