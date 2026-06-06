// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ShootZombie.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Weapon.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"
#include "Zombies/BaseZombie.h"

EBTNodeResult::Type UBTT_ShootZombie::ExecuteTask(UBehaviorTreeComponent& root, uint8* nodeMemory)
{
	FName enemyName = "ZombieToRunFrom";
	
	if (auto enemy = Cast<ABaseZombie>(root.GetBlackboardComponent()->GetValueAsObject(enemyName)))
	{
		FVector enemyLocation = enemy->GetActorLocation();
		FVector myLocation = root.GetAIOwner()->GetPawn()->GetActorLocation();
		
		FVector direction = enemyLocation - myLocation;
		
		direction.Normalize();
		
		ASurvivorPawn* mySurvivorPawn = Cast<ASurvivorPawn>(root.GetAIOwner()->GetPawn());
			
		FRotator newRotation = direction.ToOrientationRotator();
			
		mySurvivorPawn->SetActorRotation(newRotation);
			
		//weapon->UseItem(*mySurvivorPawn);
			
		UStudentPerceptorMuylleFae* myPerceptor = mySurvivorPawn->GetComponentByClass<UStudentPerceptorMuylleFae>();
			
		if (myPerceptor->UseWeapon())
		{
			GEngine->AddOnScreenDebugMessage(5, 3.f, FColor::Green,
			                                 FString::Printf(TEXT("Shot a Zombie!")));
			if (auto health = enemy->GetComponentByClass<UHealthComponent>())
			{
				if (health->IsDead())
				{
					myPerceptor->KilledEnemy(enemy);
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(5, 3.f, FColor::Red, 
	FString::Printf(TEXT("missed a Zombie!")));
			return EBTNodeResult::Failed;
			
		}
	}
	
	return EBTNodeResult::Succeeded;
}
