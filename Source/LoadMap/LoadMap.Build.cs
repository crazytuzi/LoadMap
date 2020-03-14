// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LoadMap : ModuleRules
{
	public LoadMap(ReadOnlyTargetRules Target) : base(Target)
	{
		bLegacyPublicIncludePaths = true;

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
			"MoviePlayer",
			"UMG"
		});
	}
}
