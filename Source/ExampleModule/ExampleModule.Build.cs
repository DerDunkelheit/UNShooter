// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExampleModule : ModuleRules
{
	public ExampleModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		//Allows include in headers.
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"NavigationSystem",
			"UMG",
		});
		
		//PrivateDependencyModuleNames allows include only in internal cpp files.
	}
}
