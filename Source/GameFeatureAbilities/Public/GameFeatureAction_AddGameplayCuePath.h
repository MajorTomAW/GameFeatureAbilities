// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "GameFeaturePluginURL.h"
#include "GameFeatureAction_AddGameplayCuePath.generated.h"

/**
 * GameFeatureAction responsible for adding gameplay cue paths to the gameplay cue manager.
 *
 * @see UAbilitySystemGlobals::GameplayCueNotifyPaths
 */
UCLASS(MinimalAPI, meta = (DisplayName = "Add Gameplay Cue Path"))
class UGameFeatureAction_AddGameplayCuePath : public UGameFeatureAction
{
	GENERATED_BODY()

public:
	UGameFeatureAction_AddGameplayCuePath();

	//~ Begin UGameFeatureAction Interface
	virtual void OnGameFeatureRegistering() override;
	virtual void OnGameFeatureUnregistering() override;
	//~ End UGameFeatureAction Interface

	//~ Begin UObject Interface
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
	//~ End UObject Interface

private:
	/** The name of the plugin that owns this game feature. */
	UPROPERTY(EditAnywhere, Category = "Gameplay Cues", meta = (DisplayName = "Plugin"))
	FGameFeaturePluginURL PluginURL;
	
	/**
	 * List of paths to register to the gameplay cue manager.
	 * These are relative to the game feature plugin's content directory.
	 */
	UPROPERTY(EditAnywhere, Category = "Gameplay Cues", meta = (RelativeToGameContentDir, LongPackageName))
	TArray<FDirectoryPath> GameplayCuePaths;
};
