// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorWindowExample.h"
#include "EditorWindowExampleStyle.h"
#include "EditorWindowExampleCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName EditorWindowExampleTabName("EditorWindowExample");

#define LOCTEXT_NAMESPACE "FEditorWindowExampleModule"

void FEditorWindowExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FEditorWindowExampleStyle::Initialize();
	FEditorWindowExampleStyle::ReloadTextures();

	FEditorWindowExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEditorWindowExampleCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FEditorWindowExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FEditorWindowExampleModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(EditorWindowExampleTabName, FOnSpawnTab::CreateRaw(this, &FEditorWindowExampleModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FEditorWindowExampleTabTitle", "EditorWindowExample"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FEditorWindowExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEditorWindowExampleStyle::Shutdown();

	FEditorWindowExampleCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EditorWindowExampleTabName);
}

TSharedRef<SDockTab> FEditorWindowExampleModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FEditorWindowExampleModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("EditorWindowExample.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FEditorWindowExampleModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(EditorWindowExampleTabName);
}

void FEditorWindowExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FEditorWindowExampleCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	/*{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEditorWindowExampleCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}*/
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorWindowExampleModule, EditorWindowExample)