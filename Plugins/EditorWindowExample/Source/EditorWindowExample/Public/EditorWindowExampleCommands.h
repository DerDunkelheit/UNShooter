// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorWindowExampleStyle.h"

class FEditorWindowExampleCommands : public TCommands<FEditorWindowExampleCommands>
{
public:

	FEditorWindowExampleCommands()
		: TCommands<FEditorWindowExampleCommands>(TEXT("EditorWindowExample"), NSLOCTEXT("Contexts", "EditorWindowExample", "EditorWindowExample Plugin"), NAME_None, FEditorWindowExampleStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};