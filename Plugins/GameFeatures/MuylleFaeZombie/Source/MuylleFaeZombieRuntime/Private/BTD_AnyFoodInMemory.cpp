// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_AnyFoodInMemory.h"

#include "AIController.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"

class UStudentPerceptorMuylleFae;

bool UBTD_AnyFoodInMemory::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (auto myPawnPerceptor = OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass<UStudentPerceptorMuylleFae>())
	{
		return myPawnPerceptor->AnyFoodInMemory();
	}
	
	return false;
}
