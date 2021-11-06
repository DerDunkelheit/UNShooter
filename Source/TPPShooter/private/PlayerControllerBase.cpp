// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

void APlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessEvent.Broadcast(InPawn);
}

void APlayerControllerBase::OnUnPossess()
{
	Super::OnUnPossess();

	UnPossessEvent.Broadcast();
}
