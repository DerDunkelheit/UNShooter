// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EditorFunctionsExampleActor.generated.h"

UCLASS()
class EXAMPLEMODULE_API AEditorFunctionsExampleActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEditorFunctionsExampleActor();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

protected:
	UPROPERTY(EditAnywhere)
	bool PostEditChangeBoolToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
