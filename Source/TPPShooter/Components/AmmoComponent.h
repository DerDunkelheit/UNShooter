// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPPShooter/Enums/AmmoTypeEnum.h"

#include "AmmoComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPPSHOOTER_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAmmoComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

    UFUNCTION(BlueprintCallable)
	void SetNewMaxAmmo(int Value);
	
	bool HasAmmo();
	void ConsumeAmmo(int Amount = 1);
	bool TryReload();

private:

    UPROPERTY(EditAnywhere, Category = "Settings")
	bool bUseAmmo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = true))
	AmmoTypeEnum AmmoType;
	
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
    int InitialAmmo;

	UPROPERTY(EditAnywhere,Category = "Settings")
	int MaxAmmo;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CurrentAmmo;
};
