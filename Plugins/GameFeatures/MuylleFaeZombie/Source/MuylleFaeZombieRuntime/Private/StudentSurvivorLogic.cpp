// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentSurvivorLogic.h"

#include "Items/Food.h"
#include "Items/Medkit.h"
#include "Items/Weapon.h"
#include "Zombies/BaseZombie.h"

// Sets default values for this component's properties
UStudentSurvivorLogic::UStudentSurvivorLogic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStudentSurvivorLogic::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	MySurvivorPawn = Cast<ASurvivorPawn>(GetOwner());
	MyHealth = MySurvivorPawn->GetComponentByClass<UHealthComponent>();
	MyInventory = MySurvivorPawn->GetComponentByClass<UInventoryComponent>();
	MyPerceptor = MySurvivorPawn->GetComponentByClass<UStudentPerceptorMuylleFae>();
	MyStamina = MySurvivorPawn->GetComponentByClass<UStaminaComponent>();
	
	MyPerceptor->OnPerceptedSomething.AddDynamic(this, &UStudentSurvivorLogic::OnPerceptionHappened);
}


// Called every frame
void UStudentSurvivorLogic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UStudentSurvivorLogic::OnPerceptionHappened(AActor* perceivedActor, FAIStimulus stimulus)
{
	if (auto enemy = Cast<ABaseZombie>(perceivedActor))
	{
		if (!SeenZombies.Contains(enemy))
		{
			SeenZombies.Add(enemy);
		}
	}
	
	if (auto healthKit = Cast<AMedkit>(perceivedActor))
	{
		if (!SeenMedkits.Contains(healthKit))
		{
			SeenMedkits.Add(healthKit);
		}
	}
	
	if (auto food = Cast<AFood>(perceivedActor))
	{
		if (!SeenFoods.Contains(food))
		{
			SeenFoods.Add(food);
		}
	}
	
	if (auto weapon = Cast<AWeapon>(perceivedActor))
	{
		if (!SeenWeapons.Contains(weapon))
		{
			SeenWeapons.Add(weapon);
		}
	}
}


