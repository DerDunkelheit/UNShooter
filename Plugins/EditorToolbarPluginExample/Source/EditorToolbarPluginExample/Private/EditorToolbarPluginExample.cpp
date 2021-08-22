// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorToolbarPluginExample.h"
#include "EditorToolbarPluginExampleStyle.h"
#include "EditorToolbarPluginExampleCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "AssetRegistry/AssetRegistryModule.h"

static const FName EditorToolbarPluginExampleTabName("EditorToolbarPluginExample");

#define LOCTEXT_NAMESPACE "FEditorToolbarPluginExampleModule"

void FEditorToolbarPluginExampleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FEditorToolbarPluginExampleStyle::Initialize();
	FEditorToolbarPluginExampleStyle::ReloadTextures();

	FEditorToolbarPluginExampleCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEditorToolbarPluginExampleCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FEditorToolbarPluginExampleModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FEditorToolbarPluginExampleModule::RegisterMenus));
}

void FEditorToolbarPluginExampleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEditorToolbarPluginExampleStyle::Shutdown();

	FEditorToolbarPluginExampleCommands::Unregister();
}

void FEditorToolbarPluginExampleModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	//const UClass* Class = UStaticMesh::StaticClass();
	//AssetRegistryModule.Get().GetAssetsByClass(Class->GetFName(), AssetData);
	//AssetRegistryModule.Get().GetAllAssets(AssetData);
	AssetRegistryModule.Get().GetAssetsByPath("/Game/Blueprints/Actors/EnemiesDoors", AssetData);
	
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions {2} {3}"),
							FText::FromString(TEXT("FEditorToolbarPluginExampleModule::PluginButtonClicked()")),
							FText::FromString(TEXT("EditorToolbarPluginExample.cpp")),
							FText::FromString(TEXT("You have total enemies rooms:")),
							FText::FromString(FString::FromInt(AssetData.Num()))
					   );
	
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FEditorToolbarPluginExampleModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FEditorToolbarPluginExampleCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEditorToolbarPluginExampleCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorToolbarPluginExampleModule, EditorToolbarPluginExample)