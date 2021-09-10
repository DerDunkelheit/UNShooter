// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/FP_FirstPerson/FP_PlayerController.h"

void AFP_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessEvent.Broadcast(InPawn);
}

void AFP_PlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	UnPossessEvent.Broadcast();
}
