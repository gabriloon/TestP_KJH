// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NeopleTestP_KJH : ModuleRules
{
	public NeopleTestP_KJH(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","UMG"});
	}
}
