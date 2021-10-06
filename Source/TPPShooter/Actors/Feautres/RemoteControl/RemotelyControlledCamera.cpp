// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/Actors/Feautres/RemoteControl/RemotelyControlledCamera.h"

ARemotelyControlledCamera::ARemotelyControlledCamera()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(StaticMeshComponent);
}

void ARemotelyControlledCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("SelectLeftElement", IE_Pressed, this , &ARemotelyControlledCamera::SelectLeftCamera);
	PlayerInputComponent->BindAction("SelectRightElement", IE_Pressed, this, &ARemotelyControlledCamera::SelectRightCamera);
}

void ARemotelyControlledCamera::SelectLeftCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Left"));
}

void ARemotelyControlledCamera::SelectRightCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Right"));
}