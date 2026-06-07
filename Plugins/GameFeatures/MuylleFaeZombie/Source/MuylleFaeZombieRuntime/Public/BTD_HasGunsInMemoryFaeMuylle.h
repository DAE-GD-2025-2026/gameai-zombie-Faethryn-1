// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_HasGunsInMemoryFaeMuylle.generated.h"

/**
 * 
 */
UCLASS()
class MUYLLEFAEZOMBIERUNTIME_API UBTD_HasGunsInMemoryFaeMuylle : public UBTDecorator
{
	GENERATED_BODY()
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
