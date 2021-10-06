// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RemotelyControlledPawn.h"
#include "GameFramework/Actor.h"
#include "TPPShooter/Interfaces/Interactable.h"
#include "RemoteControllerActor.generated.h"

UCLASS()
class TPPSHOOTER_API ARemoteControllerActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARemoteControllerActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bSingleControl;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (EditCondition = "bSingleControl"))
	ARemotelyControlledPawn* ControlledPawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (EditCondition = "!bSingleControl"))
	TArray<ARemotelyControlledPawn*> ControlledPawns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	ARemotelyControlledPawn* LastControlledPawn;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetLastControlledPawn(ARemotelyControlledPawn* LastPawn);

	UFUNCTION(BlueprintCallable)
	ARemotelyControlledPawn* GetControlledPawnByIndex(int Index);

	virtual void Interact_Implementation() override;

};
