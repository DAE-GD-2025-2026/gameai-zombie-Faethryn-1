// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_HasMedkitInMemoryFaeMuylle.h"

#include "AIController.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"

bool UBTD_HasMedkitInMemoryFaeMuylle::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (auto myPawnPerceptor = OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass<UStudentPerceptorMuylleFae>())
	{
		return myPawnPerceptor->AnyMedkitsInMemory();
	}
	
	return false;
}
