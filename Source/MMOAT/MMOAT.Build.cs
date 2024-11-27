// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MMOAT : ModuleRules
{
	public MMOAT(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "GameplayTasks", "GameplayTags" });
	}
}
