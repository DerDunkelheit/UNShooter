// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/DialoguesSystem/DialoguesManager.h"

void UDialoguesManager::SetupCurrentDialogues(TArray<FString> Dialogues)
{
    CurrentDialogues.Empty();

	DialogStartedEvent.Broadcast();
	
	for (auto Dialog : Dialogues)
	{
		CurrentDialogues.Enqueue(Dialog);
	}
}

void UDialoguesManager::ShowNextDialog()
{
	FString CurrentMessage;
	CurrentDialogues.Dequeue(CurrentMessage);
	if(!CurrentMessage.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1,4,FColor::Orange,CurrentMessage);
	}
	else
	{
		DialogEndedEvent.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1,4,FColor::Red,"There are no dialogues left");
	}
}

void UDialoguesManager::SetupDefaultDialogues()
{
	TArray<FString> DefaultDialogues;
	DefaultDialogues.Add("First Dialog");
	DefaultDialogues.Add("Second Dialog");
	DefaultDialogues.Add("Third Dialog");

	SetupCurrentDialogues(DefaultDialogues);
}

void UDialoguesManager::ClearDialogues()
{
    DialogEndedEvent.Broadcast();
	
	CurrentDialogues.Empty();
}
