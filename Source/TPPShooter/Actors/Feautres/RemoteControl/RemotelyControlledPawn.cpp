// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/Feautres/RemoteControl/RemotelyControlledPawn.h"

#include "Kismet/GameplayStatics.h"
#include "TPPShooter/FP_FirstPerson/FP_FirstPersonCharacter.h"
#include "TPPShooter/FP_FirstPerson/FP_PlayerController.h"

// Sets default values
ARemotelyControlledPawn::ARemotelyControlledPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMeshComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SkeletalMeshComponent);
	CameraComponent->bUsePawnControlRotation = true;
	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCaptureComponent->SetupAttachment(SkeletalMeshComponent);
}

// Called when the game starts or when spawned
void ARemotelyControlledPawn::BeginPlay()
{
	Super::BeginPlay();
	
	AFP_PlayerController* PlayerController = Cast<AFP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->PossessEvent.AddDynamic(this, &ARemotelyControlledPawn::OnTurretPossessed);
	PlayerController->UnPossessEvent.AddDynamic(this, &ARemotelyControlledPawn::OnTurretUnPossessed);

	auto* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	InitialYawMin = CameraManager->ViewYawMin;
	InitialYawMax = CameraManager->ViewYawMax;
}

// Called every frame
void ARemotelyControlledPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARemotelyControlledPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("StopPossession", IE_Pressed, this, &ARemotelyControlledPawn::StopPossession);
}

void ARemotelyControlledPawn::AddControllerYawInput(float Value)
{
	Super::AddControllerYawInput(Value);
}

void ARemotelyControlledPawn::AddControllerPitchInput(float Value)
{
	Super::AddControllerPitchInput(Value);
}

void ARemotelyControlledPawn::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	SceneCaptureComponent->SetWorldTransform(CameraComponent->GetComponentTransform());
}

void ARemotelyControlledPawn::SetPreviousPawn(APawn* PreviousPawn)
{
	PreviousPossessedPawn = PreviousPawn;
}

void ARemotelyControlledPawn::StopPossession()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop possesing"));

    auto* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	LastPawnRotator = PlayerController->GetControlRotation();
	PlayerController->Possess(PreviousPossessedPawn);
	
	auto* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	CameraManager->ViewYawMin = InitialYawMin;
	CameraManager->ViewYawMax = InitialYawMax;
}
