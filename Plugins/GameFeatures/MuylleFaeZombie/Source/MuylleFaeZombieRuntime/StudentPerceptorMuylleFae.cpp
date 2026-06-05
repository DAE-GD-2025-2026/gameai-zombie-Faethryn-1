// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorMuylleFae.h"

#include "SurvivorAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Food.h"
#include "Items/Medkit.h"
#include "Items/Weapon.h"
#include "Survivor/SurvivorPawn.h"
#include "Zombies/BaseZombie.h"
#include "Common/InventoryComponent.h"
#include "Common/HealthComponent.h"
#include "Common/StaminaComponent.h"


UStudentPerceptorMuylleFae::UStudentPerceptorMuylleFae()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptorMuylleFae::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptorMuylleFae::OnPerceptionUpdated);
	}
	
	MySurvivorPawn = Cast<ASurvivorPawn>(GetOwner());
	MyHealth = MySurvivorPawn->GetComponentByClass<UHealthComponent>();
	MyInventory = MySurvivorPawn->GetComponentByClass<UInventoryComponent>();
	MyStamina = MySurvivorPawn->GetComponentByClass<UStaminaComponent>();
}

void UStudentPerceptorMuylleFae::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	
	auto name = Actor->GetName();
	
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, name);
	if (auto enemy = Cast<ABaseZombie>(Actor))
	{
		if (!SeenZombies.Contains(enemy))
		{
			SeenZombies.Add(enemy);
		}
		SurvivorSawZombieInRange(enemy);
	}
	
	if (auto healthKit = Cast<AMedkit>(Actor))
	{
		if (!SeenMedkits.Contains(healthKit))
		{
			SeenMedkits.Add(healthKit);
		}
	}
	
	if (auto food = Cast<AFood>(Actor))
	{
		if (!SeenFoods.Contains(food))
		{
			SeenFoods.Add(food);
		}
	}
	
	if (auto weapon = Cast<AWeapon>(Actor))
	{
		if (!SeenWeapons.Contains(weapon))
		{
			SeenWeapons.Add(weapon);
		}
	}
	
}

bool UStudentPerceptorMuylleFae::ZombieRangeCheck(ABaseZombie* zombieToCheck)
{
	FVector playerLocation = MySurvivorPawn->GetActorLocation();
	
	FVector zombieLocation = zombieToCheck->GetActorLocation();
	
	float distance = FVector::Distance(playerLocation, zombieLocation);
	
	if (distance < ZombieRunRange)
	{
		return true;
	}
	
	return false;
}

void UStudentPerceptorMuylleFae::SurvivorSawZombieInRange(ABaseZombie* zombie)
{
	//if (ZombieRangeCheck(zombie))
	//{
	GEngine->AddOnScreenDebugMessage(5, 3.f, FColor::Green, 
	FString::Printf(TEXT("Saw a Zombie!")));
		if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
		{
			myController->GetBlackboardComponent()->SetValueAsObject(FName("ZombieToRunFrom"), zombie);
		}
	//}
}
