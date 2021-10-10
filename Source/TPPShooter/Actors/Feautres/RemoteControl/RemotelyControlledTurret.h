// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RemotelyControlledPawn.h"
#include "GameFramework/Pawn.h"
#include "RemotelyControlledTurret.generated.h"

UCLASS()
class TPPSHOOTER_API ARemotelyControlledTurret : public ARemotelyControlledPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARemotelyControlledTurret();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	USkeletalMeshComponent* SkeletalMeshComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};