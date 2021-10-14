// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPPShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ATPPShooterCharacter

ATPPShooterCharacter::ATPPShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	ItemDropPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ItemDropPosition"));
	ItemDropPosition->SetupAttachment(RootComponent);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	ZoomComponent = CreateDefaultSubobject<UZoomComponent>(TEXT("Zoom Component"));

	CharacterWeaponSocket = "Weapon_Socket";
}


void ATPPShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthDepleted.AddDynamic(this, &ATPPShooterCharacter::DieEvent);
}

void ATPPShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATPPShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATPPShooterCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ATPPShooterCharacter::EndCrouch);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractionComponent, &UInteractionComponent::TryInteract);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, ZoomComponent, &UZoomComponent::StartZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, ZoomComponent, &UZoomComponent::EndZoom);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ATPPShooterCharacter::StartFire);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ATPPShooterCharacter::EndFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATPPShooterCharacter::ReloadWeapon);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATPPShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPPShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ATPPShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ATPPShooterCharacter::LookUpAtRate);
}

void ATPPShooterCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		//TODO: create an interface for characters, so AI enemies can use inventory as well.
		//Item->Use(this);
	}
}

void ATPPShooterCharacter::RemoveItemFormInventory(UItem* Item)
{
	if (Item)
	{
		Inventory->RemoveItem(Item);
	}
}

void ATPPShooterCharacter::AddItemToInventory(UItem* Item)
{
	if (Item)
	{
		Inventory->AddItem(Item);
	}
}

void ATPPShooterCharacter::DropItem(UItem* Item)
{
	if (Item)
	{
		Inventory->DropItem(Item);
	}
}

FVector ATPPShooterCharacter::GetPawnViewLocation() const
{
	if (FollowCamera)
	{
		return FollowCamera->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

void ATPPShooterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATPPShooterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATPPShooterCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATPPShooterCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATPPShooterCharacter::BeginCrouch()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		Crouch();
	}
}

void ATPPShooterCharacter::EndCrouch()
{
	UnCrouch();
}

void ATPPShooterCharacter::SetupInitialWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Owner = this;
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(InitialWeapon, FVector::ZeroVector, FRotator::ZeroRotator,SpawnParameters);
	CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, CharacterWeaponSocket);
}

void ATPPShooterCharacter::StartFire()
{
	if (CurrentWeapon && !bReload)
	{
		CurrentWeapon->StartFire();
		bUseControllerRotationYaw = true;
	}
}

void ATPPShooterCharacter::EndFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->EndFire();
		bUseControllerRotationYaw = false;
	}
}

void ATPPShooterCharacter::ReloadWeapon()
{
	if (CurrentWeapon && !bIsCrouched)
	{
		if(!bReload)
		{
			if (CurrentWeapon->TryReload())
			{
				bReload = true;
			}
		}
	}
}
