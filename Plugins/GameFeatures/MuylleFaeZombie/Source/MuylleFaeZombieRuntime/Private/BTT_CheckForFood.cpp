// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CheckForFood.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Food.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UBTT_CheckForFood::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	UStudentPerceptorMuylleFae* myPerceptorMuylleFae = myPawn->GetComponentByClass<UStudentPerceptorMuylleFae>();
	
	float closestFoodDistance = FLT_MAX;
	
	FVector myLocation = myPawn->GetActorLocation();
	
	AFood* currentClosestFood = nullptr;
	
	if (myPerceptorMuylleFae->SeenMedkits.Num() > 0)
	{
		for (auto food : myPerceptorMuylleFae->SeenFoods)
		{
			FVector gunLocation = food->GetActorLocation();
			
			float distance = FVector::Distance(myLocation, gunLocation);
			
			if (distance < closestFoodDistance)
			{
				currentClosestFood = food;
				closestFoodDistance = distance;
			}
		}
	}
	
	if (currentClosestFood != nullptr)
	{
		FName itemToGrabKey = "ItemToChase";
		
		root.GetBlackboardComponent()->SetValueAsObject(itemToGrabKey, currentClosestFood);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}