// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/HealthComponent.h"
#include "Components/InteractionComponent.h"
#include "GameFramework/Character.h"
#include "Items/Item.h"
#include "TPPShooter/Weapons/Weapon.h"

#include "FP_FirstPersonCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USoundBase;
class UAnimMontage;

UCLASS(config=Game)
class AFP_FirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	//TODO: replace to setting menu.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0"))

	float MouseSensitivity;

public:
	AFP_FirstPersonCharacter();

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/* This is when calculating the trace to determine what the weapon has hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WeaponRange;

	/* This is multiplied by the direction vector when the weapon trace hits something to apply velocity to the component that is hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WeaponDamage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName CharacterWeaponSocket;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AWeapon> InitialWeapon;

public:
	UFUNCTION(BlueprintCallable)
	UAnimInstance* GetWeaponMeshAnimInstance() const { return Mesh1P->GetAnimInstance(); }

	UFUNCTION(BlueprintCallable)
	void SetupInitialWeapon();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void IncreaseTemporarySpeed(float AdditionalSpeedValue, float Duration);

	UFUNCTION(BlueprintCallable)
	void AddItem(UItem* newItem);

	UFUNCTION(BlueprintCallable)
	void DropItem(UItem* item);

	UFUNCTION(BlueprintCallable)
	const FTransform& GetItemDropTransform();

	UFUNCTION(BlueprintCallable)
	UHealthComponent* GetHealthComponent();

	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual void AddControllerYawInput(float Val) override;
	virtual void AddControllerPitchInput(float Val) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USceneComponent* ItemDropPosition;

protected:
	virtual void BeginPlay() override;
	void OnFire();
	void EndFire();
	USkeletalMeshComponent* GetWeaponMesh() const { return Mesh1P; }
	void MoveForward(float Val);
	void MoveRight(float Val);
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void DieEvent();
};
