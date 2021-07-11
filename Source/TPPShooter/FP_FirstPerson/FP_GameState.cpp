// Fill out your copyright notice in the Description page of Project Settings.


#include "TPPShooter/FP_FirstPerson/FP_GameState.h"

AFP_GameState::AFP_GameState()
{
	PlayerKillCount = 0;
}

void AFP_GameState::IncreasePlayerKills()
{
	PlayerKillCount++;
}
