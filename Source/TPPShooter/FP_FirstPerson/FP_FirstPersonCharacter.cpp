// Copyright Epic Games, Inc. All Rights Reserved.

#include "FP_FirstPersonCharacter.h"

#include "DrawDebugHelpers.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "GameplayUtilities/GameUtils.h"
#include "Interfaces/HighlightInterface.h"
#include "Kismet/GameplayStatics.h"
#include "TPPShooter/NonUClasses/GameDebuggerNew.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel1
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFP_FirstPersonCharacter

AFP_FirstPersonCharacter::AFP_FirstPersonCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCompnent"));
	SpringArm->SetupAttachment(GetMesh());

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->SetupAttachment(SpringArm);
	
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);				// Set so only owner can see mesh
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);	// Attach mesh to FirstPersonCameraComponent
	Mesh1P->bCastDynamicShadow = false;			// Disallow mesh to cast dynamic shadows
	Mesh1P->CastShadow = false;				// Disallow mesh to cast other shadows

	// Set weapon damage and range
	WeaponRange = 5000.0f;
	WeaponDamage = 500000.0f;
	
	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	ItemDropPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ItemDrop"));
	ItemDropPosition->SetupAttachment(RootComponent);

	CharacterWeaponSocket = "WeaponSocket";
}

void AFP_FirstPersonCharacter::TestHotReload()
{
	int test = 15;
	GEngine->AddOnScreenDebugMessage(2, 2, FColor::Cyan, FString::FromInt(test));
}

void AFP_FirstPersonCharacter::SetupInitialWeapon()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Owner = this;
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(InitialWeapon, FVector::ZeroVector, FRotator::ZeroRotator,SpawnParameters);
	CurrentWeapon->AttachToComponent(GetWeaponMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, CharacterWeaponSocket);
}

/*
void AFP_FirstPersonCharacter::AddControllerYawInput(float Val)
{
	Super::AddControllerYawInput(Val * MouseSensitivity);
}

void AFP_FirstPersonCharacter::AddControllerPitchInput(float Val)
{
	Super::AddControllerPitchInput(Val * MouseSensitivity);
}
*/

void AFP_FirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthDepleted.AddDynamic(this, &AFP_FirstPersonCharacter::DieEvent);
}

void AFP_FirstPersonCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FindActorsForHighlight();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFP_FirstPersonCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	
	// Set up gameplay key bindings

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	// Bind fire event
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AFP_FirstPersonCharacter::OnFire);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AFP_FirstPersonCharacter::EndFire);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractionComponent, &UInteractionComponent::TryInteract);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFP_FirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFP_FirstPersonCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AFP_FirstPersonCharacter::OnFire()
{
	if(CurrentWeapon != nullptr)
	{
		CurrentWeapon->StartFire();
	}
}

void AFP_FirstPersonCharacter::EndFire()
{
	if(CurrentWeapon != nullptr)
	{
		CurrentWeapon->EndFire();
	}
}

void AFP_FirstPersonCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFP_FirstPersonCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFP_FirstPersonCharacter::AddItem(UItem* newItem)
{
	if(newItem)
	{
		InventoryComponent->AddItem(newItem);
	}
}

void AFP_FirstPersonCharacter::DropItem(UItem* item)
{
	if(item)
	{
		InventoryComponent->DropItem(item);
	}
}

const FTransform& AFP_FirstPersonCharacter::GetItemDropTransform()
{
	return ItemDropPosition->GetComponentTransform();
}

UHealthComponent* AFP_FirstPersonCharacter::GetHealthComponent()
{
	return HealthComponent;
}

void AFP_FirstPersonCharacter::FindActorsForHighlight()
{
	AActor* hitActor;
	FVector traceStart;
	FVector traceEnd;
	if(GameUtils::TryHitFromEye(this, 600, hitActor, traceStart, traceEnd))
	{
		if(hitActor->GetClass()->ImplementsInterface(UHighlightInterface::StaticClass()))
		{
			IHighlightInterface::Execute_Highlight(hitActor, 0.1f);
		}
	}

	if(ConsoleDebug::IsDebugHighlightDrawingEnable())
	{
	   DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Orange, false, 2);
	}
}