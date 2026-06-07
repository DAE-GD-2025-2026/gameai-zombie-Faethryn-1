// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GrabCurrentItemFaeMuylle.generated.h"

/**
 * 
 */
UCLASS()
class MUYLLEFAEZOMBIERUNTIME_API UBTT_GrabCurrentItemFaeMuylle : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory) override;
};
