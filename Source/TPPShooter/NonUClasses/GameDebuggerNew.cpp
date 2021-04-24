#include "GameDebuggerNew.h"

static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(
	TEXT("Game.DebugWeapons"),
	DebugWeaponDrawing,
	TEXT("Draw Debug Lines for Weapons"),
	ECVF_Cheat);

static int32 DebugInteractiveDrawing = 0;
FAutoConsoleVariableRef CVARDebugInteractiveDrawing(
	TEXT("Game.DebugInteraction"),
	DebugInteractiveDrawing,
	TEXT("Draw Debug Lines for Interaction"),
	ECVF_Cheat);

bool GameDebuggerNew::IsDebugWeaponEnable()
{
	return DebugWeaponDrawing > 0;
}

bool GameDebuggerNew::IsDebugInteractionEnable()
{
	return DebugInteractiveDrawing > 0;
}