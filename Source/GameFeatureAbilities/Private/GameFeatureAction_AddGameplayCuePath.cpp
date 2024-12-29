// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameFeatureAction_AddGameplayCuePath.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include "AbilitySystemGlobals.h"
#include "GameFeaturesSubsystem.h"
#include "GameFeaturesSubsystemSettings.h"
#include "GameplayCueManager.h"
#include "GameplayCueSet.h"
#include "Engine/AssetManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameFeatureAction_AddGameplayCuePath)

#define LOCTEXT_NAMESPACE "GameFeatures"

UGameFeatureAction_AddGameplayCuePath::UGameFeatureAction_AddGameplayCuePath()
{
	// Add a default path that is commonly used
	GameplayCuePaths.Add(FDirectoryPath(TEXT("/GameplayCues")));

	PluginName = FString();
}

void UGameFeatureAction_AddGameplayCuePath::OnGameFeatureRegistering()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UGameFeatureAction_AddGameplayCuePath::OnGameFeatureRegistering);

	const FString PluginRootPath = TEXT("/") + PluginName;

	UGameplayCueManager* CueManager = UAbilitySystemGlobals::Get().GetGameplayCueManager();
	if (CueManager)
	{
		UGameplayCueSet* RuntimeCueSet = CueManager->GetRuntimeCueSet();
		const int32 PreInitializeNumCues = RuntimeCueSet ? RuntimeCueSet->GameplayCueData.Num() : 0;

		// Add the paths to the cue manager
		for (const FDirectoryPath& Directory : GameplayCuePaths)
		{
			FString MutablePath = Directory.Path;
			UGameFeaturesSubsystem::FixPluginPackagePath(MutablePath, PluginRootPath, false);
			CueManager->AddGameplayCueNotifyPath(MutablePath, false);
		}

		// Rebuild the runtime library if we added any new cues
		if (!GameplayCuePaths.IsEmpty())
		{
			CueManager->InitializeRuntimeObjectLibrary();
		}

		// Let the asset manager now about the new cues
		const int32 PostInitializeNumCues = RuntimeCueSet ? RuntimeCueSet->GameplayCueData.Num() : 0;
		if (PreInitializeNumCues != PostInitializeNumCues)
		{
			TArray<FSoftObjectPath> CuePaths;
			RuntimeCueSet->GetSoftObjectPaths(CuePaths);

			FAssetBundleData BundleData;
			BundleData.AddBundleAssetsTruncated(UGameFeaturesSubsystemSettings::LoadStateClient, CuePaths);

			FPrimaryAssetId PrimaryAssetId = FPrimaryAssetId("GameplayCueRefs", "GameplayCueReferences");
			UAssetManager::Get().AddDynamicAsset(PrimaryAssetId, FSoftObjectPath(), BundleData);
		}
	}
}

void UGameFeatureAction_AddGameplayCuePath::OnGameFeatureUnregistering()
{
	const FString PluginRootPath = TEXT("/") + PluginName;

	UGameplayCueManager* CueManager = UAbilitySystemGlobals::Get().GetGameplayCueManager();
	if (CueManager)
	{
		int32 NumRemoved = 0;
		for (const FDirectoryPath& Directory : GameplayCuePaths)
		{
			FString MutablePath = Directory.Path;
			UGameFeaturesSubsystem::FixPluginPackagePath(MutablePath, PluginRootPath, false);
			NumRemoved += CueManager->RemoveGameplayCueNotifyPath(MutablePath, false);
		}

		ensure(NumRemoved == GameplayCuePaths.Num());

		// Rebuild the runtime library if we removed any cues
		if (NumRemoved > 0)
		{
			CueManager->InitializeRuntimeObjectLibrary();
		}
	}
}

#if WITH_EDITOR
EDataValidationResult UGameFeatureAction_AddGameplayCuePath::IsDataValid(class FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (PluginName.IsEmpty())
	{
		const FText Message = LOCTEXT("EmptyPluginName", "PluginName must be set!");
		Context.AddError(Message);
		Result = EDataValidationResult::Invalid;
	}

	for (const FDirectoryPath& Directory : GameplayCuePaths)
	{
		if (Directory.Path.IsEmpty())
		{
			const FText Message = FText::Format(LOCTEXT("EmptyPath", "'{0}' is not a valid path!"), FText::FromString(Directory.Path));
			Context.AddError(Message);
			Result = EDataValidationResult::Invalid;
		}
	}

	return Result;
}
#endif

#undef LOCTEXT_NAMESPACE