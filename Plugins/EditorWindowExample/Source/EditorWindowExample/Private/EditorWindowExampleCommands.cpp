// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorWindowExampleCommands.h"

#define LOCTEXT_NAMESPACE "FEditorWindowExampleModule"

void FEditorWindowExampleCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "EditorWindowExample", "Bring up EditorWindowExample window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
