// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MMOAT : ModuleRules
{
    public MMOAT(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // Ajouter les chemins d'inclusion publics et privés
        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Public")
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private")
            }
        );

        // Modules requis pour ce module
        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput", 
            "GameplayAbilities", 
            "GameplayTasks", 
            "GameplayTags" 
        });

        // Modules privés (si nécessaire)
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
