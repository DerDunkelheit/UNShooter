// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

//Blueprints will bind to this to update the UI.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepleted);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPPSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(AActor* DamagedActor,float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void RestoreHealth(float Value);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() { return CurrentHealth; }

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnHealthDepleted OnHealthDepleted;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float InitialHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	bool bDebugMode = false;
	
private:
	float CurrentHealth;

	void TriggerDie() {OnHealthDepleted.Broadcast();};
};
