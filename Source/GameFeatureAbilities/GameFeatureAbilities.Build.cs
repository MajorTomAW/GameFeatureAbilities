// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameFeatureAbilities : ModuleRules
{
	public GameFeatureAbilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new[] 
		{ 
			"Core",
			"GameFeatures",
			"GameplayAbilities"
		});
			
		
		PrivateDependencyModuleNames.AddRange(new[]
		{ 
			"CoreUObject", 
			"Engine",
		});
	}
}
