// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GrabCurrentItemFaeMuylle.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/BaseItem.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_GrabCurrentItemFaeMuylle::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	UStudentPerceptorMuylleFae* myPerceptorMuylleFae = myPawn->GetComponentByClass<UStudentPerceptorMuylleFae>();
		
	FName itemKey = "ItemToChase";
		
	if (auto item = Cast<ABaseItem>(root.GetBlackboardComponent()->GetValueAsObject(itemKey)))
	{
		myPerceptorMuylleFae->GrabItem(item);
		
		root.GetBlackboardComponent()->SetValueAsObject(itemKey, nullptr);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
