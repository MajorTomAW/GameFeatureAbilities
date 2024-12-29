// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction_WorldActionBase.h"
#include "GameFeatureAction_AddAbilities.generated.h"

/**
 * GameFeatureAction responsible for adding abilities and attributes to actors in the world.
 */
UCLASS(MinimalAPI, meta = (DisplayName = "Add Abilities"))
class UGameFeatureAction_AddAbilities : public UGameFeatureAction_WorldActionBase
{
	GENERATED_BODY()
};
