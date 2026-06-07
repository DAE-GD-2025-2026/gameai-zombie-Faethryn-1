// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ESurvivorModeFaeMuylle.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class UESurvivorModeFaeMuylle : uint8
{
	Wandering = 0,
	EvadeZombie = 1,
	ExploreHouse = 2,
	RunFromPurgeZone = 3,
};
