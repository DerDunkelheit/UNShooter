// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorToolbarPluginExampleStyle.h"

class FEditorToolbarPluginExampleCommands : public TCommands<FEditorToolbarPluginExampleCommands>
{
public:

	FEditorToolbarPluginExampleCommands()
		: TCommands<FEditorToolbarPluginExampleCommands>(TEXT("EditorToolbarPluginExample"), NSLOCTEXT("Contexts", "EditorToolbarPluginExample", "EditorToolbarPluginExample Plugin"), NAME_None, FEditorToolbarPluginExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
