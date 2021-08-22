// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorToolbarPluginExampleCommands.h"

#define LOCTEXT_NAMESPACE "FEditorToolbarPluginExampleModule"

void FEditorToolbarPluginExampleCommands::RegisterCommands()
{
	//Here we can change the name.
	UI_COMMAND(PluginAction, "Some custom name", "Execute EditorToolbarPluginExample action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
