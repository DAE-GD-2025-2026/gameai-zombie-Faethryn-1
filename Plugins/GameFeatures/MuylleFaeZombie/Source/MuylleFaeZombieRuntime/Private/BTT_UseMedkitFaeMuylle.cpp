// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_UseMedkitFaeMuylle.h"

#include "AIController.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"

class UStudentPerceptorMuylleFae;

EBTNodeResult::Type UBTT_UseMedkitFaeMuylle::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	if (auto myPawnPerceptor = root.GetAIOwner()->GetPawn()->GetComponentByClass<UStudentPerceptorMuylleFae>())
	{
		myPawnPerceptor->UseMedkitInInventory();
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
