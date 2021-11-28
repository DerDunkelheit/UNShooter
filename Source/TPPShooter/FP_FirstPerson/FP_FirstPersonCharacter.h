// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/HealthComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/Item.h"
#include "TPPShooter/Weapons/Weapon.h"

#include "FP_FirstPersonCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USoundBase;
class UAnimMontage;
class USoundCue;

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

	//virtual void AddControllerYawInput(float Val) override;
	//virtual void AddControllerPitchInput(float Val) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USceneComponent* ItemDropPosition;

	//TODO: rework them in more suitable way fro my project.
	//LPShooter fields
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;
	//Sound Cue played when this character aims their weapon. This can just be left empty for games that do not need an aiming sound.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Audio")
	USoundCue* SoundCueAim;

	//Sound Cue played when this character jumps. It only plays once, as soon as the character leaves the ground.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Audio")
	USoundCue* SoundCueJump;

	//Maximum speed at which the character can move when walking. This value may be modified by a myriad of other values in this blueprint based on the situation, like the sideways and backward movement multipliers.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Movement Settings")
	float SpeedWalking = 400.0f;

	//Maximum speed at which this character can move when running.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Movement Settings")
	float SpeedRunning = 700.0f;

	//Maximum speed at which the character can move when walking and aiming their weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Movement Settings")
	float SpeedAiming = 350.0f;

	//Montage played when the character fires their weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageFire;

	//Montage played when the character inspects a weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageInspect;

	//Montage played when the character reloads.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageReload;

	//Montage played when the character reloads while having no ammo in their weapon's magazine.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageReloadEmpty;

	//Animation Montage played when trying to holster the character's weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageHolster;

	//Animation Montage played when the character is unholstering their weapon.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Animation")
	UAnimMontage* MontageUnholster;

	//Offset from the top of the character's capsule at which the first-person will be located.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | View")
	FVector ViewOffset = FVector(0.0f, 0.0f, -35.0f);

	//Type of Weapon used by this Character. Will determine what Weapon is spawned when starting to play this Character.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack Sample | Character | Settings")
	TSubclassOf<AActor> ClassWeapon;
	
	//If true, the Character's Weapon is holstered.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHolstered;

	//If true, the Character is aiming.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bAiming;

	//If true, the Character is jumping.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bJumping;

	//If true, the Character is running.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bRunning;

	//Returns true if the player is currently holding the run key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyRun;

	//Returns true if the player is currently holding the aim key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyAim;

	//Returns true if the player is currently holding the fire key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyFire;

	//Returns true if the player is currently holding the crouch key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyCrouch;

	//Returns true if the player is currently holding the jump key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyJump;

	//Returns true if the player is currently holding the tutorial key.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bHoldingKeyTutorial;

	//Returns true if this Character is currently in the middle of playing the Inspect Montage.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bPlayingMontageInspecting;

	//Returns true if this Character is currently in the middle of playing a Reload Montage.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bPlayingMontageReloading;

	//Returns true if this Character is currently in the middle of playing a Holster Montage.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bPlayingMontageHolstering;

	//Weapon Actor.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	AActor* ActorWeapon;

	//Returns the time at which the Character last fired a Weapon.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float LastFireTime;

	//Pitch Input.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float Pitch;

	//Yaw Input.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float Yaw;

	//Horizontal Input.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float Horizontal;

	//Vertical Input.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float Vertical;

	//Is the Weapon's ammunition empty?
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	bool bIsWeaponEmpty;

	//Weapon Rate Of Fire.
	UPROPERTY(BlueprintReadWrite, Category = "Low Poly Shooter Pack Sample | Data")
	float RateOfFire;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void OnFire();
	void EndFire();
	USkeletalMeshComponent* GetWeaponMesh() const { return Mesh1P; }
	void MoveForward(float Val);
	void MoveRight(float Val);
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void DieEvent();

private:
	void FindActorsForHighlight();
};
