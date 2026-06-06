// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CheckForGuns.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"
#include "Survivor/SurvivorPawn.h"
#include "Items/Weapon.h"

EBTNodeResult::Type UBTT_CheckForGuns::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
	UStudentPerceptorMuylleFae* myPerceptorMuylleFae = myPawn->GetComponentByClass<UStudentPerceptorMuylleFae>();
	
	float closestGunDistance = FLT_MAX;
	
	FVector myLocation = myPawn->GetActorLocation();
	
	AWeapon* currentClosestWeapon = nullptr;
	
	if (myPerceptorMuylleFae->SeenWeapons.Num() > 0)
	{
		for (auto gun : myPerceptorMuylleFae->SeenWeapons)
		{
			FVector gunLocation = gun->GetActorLocation();
			
			float distance = FVector::Distance(myLocation, gunLocation);
			
			if (distance < closestGunDistance)
			{
				currentClosestWeapon = gun;
				closestGunDistance = distance;
			}
		}
	}
	
	if (currentClosestWeapon != nullptr)
	{
		FName itemToGrabKey = "ItemToChase";
		
		root.GetBlackboardComponent()->SetValueAsObject(itemToGrabKey, currentClosestWeapon);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
