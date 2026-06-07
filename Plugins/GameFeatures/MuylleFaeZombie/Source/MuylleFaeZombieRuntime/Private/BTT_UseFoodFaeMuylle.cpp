// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_UseFoodFaeMuylle.h"

#include "AIController.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"

EBTNodeResult::Type UBTT_UseFoodFaeMuylle::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	if (auto myPawnPerceptor = root.GetAIOwner()->GetPawn()->GetComponentByClass<UStudentPerceptorMuylleFae>())
	{
		myPawnPerceptor->UseFoodInInventory();
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
