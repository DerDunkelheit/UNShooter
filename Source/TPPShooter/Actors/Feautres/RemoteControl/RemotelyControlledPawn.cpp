// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/Feautres/RemoteControl/RemotelyControlledPawn.h"

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
