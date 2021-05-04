// Fill out your copyright notice in the Description page of Project Settings.


#include "LogSystem.h"

void ULogSystem::Message(FString message, FColor messageColor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, messageColor, message);
}
