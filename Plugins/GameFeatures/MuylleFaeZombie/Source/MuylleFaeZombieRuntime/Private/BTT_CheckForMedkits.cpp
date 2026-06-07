
// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CheckForMedkits.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Medkit.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_CheckForMedkits::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	UStudentPerceptorMuylleFae* myPerceptorMuylleFae = myPawn->GetComponentByClass<UStudentPerceptorMuylleFae>();
	
	float closestMedkitDistance = FLT_MAX;
	
	FVector myLocation = myPawn->GetActorLocation();
	
	AMedkit* currentClosestMedkit = nullptr;
	
	if (myPerceptorMuylleFae->SeenMedkits.Num() > 0)
	{
		for (auto Medkit : myPerceptorMuylleFae->SeenMedkits)
		{
			FVector gunLocation = Medkit->GetActorLocation();
			
			float distance = FVector::Distance(myLocation, gunLocation);
			
			if (distance < closestMedkitDistance)
			{
				currentClosestMedkit = Medkit;
				closestMedkitDistance = distance;
			}
		}
	}
	
	if (currentClosestMedkit != nullptr)
	{
		FName itemToGrabKey = "ItemToChase";
		
		root.GetBlackboardComponent()->SetValueAsObject(itemToGrabKey, currentClosestMedkit);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
