// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFeatureAbilities.h"

#define LOCTEXT_NAMESPACE "FGameFeatureAbilitiesModule"

void FGameFeatureAbilitiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGameFeatureAbilitiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameFeatureAbilitiesModule, GameFeatureAbilities)