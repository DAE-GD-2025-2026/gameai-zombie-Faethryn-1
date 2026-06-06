// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_HasCheckedHouse.h"

#include "AIController.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_HasCheckedHouse::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	UStudentPerceptorMuylleFae* myPerceptorMuylleFae = myPawn->GetComponentByClass<UStudentPerceptorMuylleFae>();
	
	myPerceptorMuylleFae->HouseChecked();
	
	return EBTNodeResult::Succeeded;
}
