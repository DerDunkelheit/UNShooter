// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIControllerBase::UpdateTargetActorKey(AActor* NewActor)
{
	//TODO: come up how to get this name dynamically
	const FName TargetActorName = "TargetActor";

	Blackboard->SetValueAsObject(TargetActorName, NewActor);
}

void AAIControllerBase::UpdateHasLineOfSight(bool HasSight)
{
	const FName HasLineOfSightName = "HasLineOfSight";

	Blackboard->SetValueAsBool(HasLineOfSightName, HasSight);
}
