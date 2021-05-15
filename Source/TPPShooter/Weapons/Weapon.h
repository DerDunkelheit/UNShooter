// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AmmoComponent.h"

#include "Weapon.generated.h"

UCLASS()
class TPPSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UAmmoComponent* AmmoComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (Tooltip = "Shots per second"))
	float RateOfFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AActor> WeaponMagazine;

	UFUNCTION(BlueprintImplementableEvent)
	void OnOwnerDied();

	UFUNCTION(BlueprintImplementableEvent)
	void OnFire();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartFire();
	UFUNCTION(BlueprintCallable)
	void EndFire();
	bool TryReload() const { return AmmoComponent->TryReload(); }
	TSubclassOf<AActor> GetWeaponMagazine() const { return WeaponMagazine; }

private:
	void Subscribe();
	void Fire();

	float LastFireTime;
	float TimerBetweenShot;
	FTimerHandle TimerHandle_TimeBetweenShots;
};
