#pragma once

#include "CoreMinimal.h"

#include "Components/HealthComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/ZoomComponent.h"
#include "GameFramework/Character.h"
#include "Items/Item.h"
#include "Weapons/Weapon.h"


#include "TPPShooterCharacter.generated.h"

UCLASS(config=Game)
class ATPPShooterCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

public:
	ATPPShooterCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UZoomComponent* ZoomComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	USceneComponent* ItemDropPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeapon* CurrentWeapon;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void BeginCrouch();
	void EndCrouch();

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent)
	void DieEvent();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemFormInventory(UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(UItem* Item);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthDepleted();

	virtual FVector GetPawnViewLocation() const override;

	FTransform GetItemDropTransform() { return ItemDropPosition->GetComponentTransform(); }

	//TODO: came up with better solution.
	UInventoryComponent* GetInventoryComponent() const {return Inventory;}

private:
	void StartFire();
	void EndFire();
	void ReloadWeapon();
};
