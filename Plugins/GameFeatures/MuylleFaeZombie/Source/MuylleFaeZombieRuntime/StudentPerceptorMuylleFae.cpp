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
#include "Village/House/House.h"

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

void UStudentPerceptorMuylleFae::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStudentPerceptorMuylleFae::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	
	auto name = Actor->GetName();
	
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, name);
	
	//Determine type of object seen
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
		SawMedkit(healthKit);
	}
	
	if (auto food = Cast<AFood>(Actor))
	{
		SawFood(food);
	}
	
	if (auto weapon = Cast<AWeapon>(Actor))
	{
		SawWeapon(weapon);
	}
	
	if (auto house = Cast<AHouse>(Actor))
	{
		SawHouse(house);
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
	if (ZombieRangeCheck(zombie))
	{
	GEngine->AddOnScreenDebugMessage(5, 3.f, FColor::Green, 
	FString::Printf(TEXT("Saw a Zombie!")));
		if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
		{
			myController->GetBlackboardComponent()->SetValueAsObject(FName("ZombieToRunFrom"), zombie);
			myController->GetBlackboardComponent()->SetValueAsEnum(FName("SurvivorMode"), 1);
		}
		MySurvivorPawn->StartRunning();
	}
}

void UStudentPerceptorMuylleFae::SawFood(AFood* food)
{
	if (!SeenFoods.Contains(food))
	{
		SeenFoods.Add(food);
	}
}

void UStudentPerceptorMuylleFae::SawMedkit(AMedkit* medkit)
{
	if (!SeenMedkits.Contains(medkit))
	{
		SeenMedkits.Add(medkit);
	}
}

void UStudentPerceptorMuylleFae::SawWeapon(AWeapon* weapon)
{
	if (!SeenWeapons.Contains(weapon))
	{
		SeenWeapons.Add(weapon);
	}
}

void UStudentPerceptorMuylleFae::SawHouse(AHouse* house)
{
	if (CheckedHouses.Contains(house))
	{
		return;
	}
	
	if (!SeenHouses.Contains(house))
	{
		SeenHouses.Add(house);
	}
	
	if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
	{
		myController->GetBlackboardComponent()->SetValueAsObject(FName("HouseMiddle"), house);
		
		if (myController->GetBlackboardComponent()->GetValueAsEnum(FName("SurvivorMode")) == 1)
		{
			return;
		}
		myController->GetBlackboardComponent()->SetValueAsEnum(FName("SurvivorMode"), 2);
	}
}

bool UStudentPerceptorMuylleFae::HasWeapon()
{
	TArray<ABaseItem*> myItems = MyInventory->GetInventory();
	
	if (myItems[weaponSlot] == nullptr)
	{
		return false;
	}
	
	if (auto weapon = Cast<AWeapon>(myItems[weaponSlot]))
	{
		return true;
	}
	
	return false;
}

AWeapon* UStudentPerceptorMuylleFae::GetWeapon()
{
	TArray<ABaseItem*> myItems = MyInventory->GetInventory();
	
	if (myItems[weaponSlot] == nullptr)
	{
		return nullptr;
	}
	
	if (auto weapon = Cast<AWeapon>(myItems[weaponSlot]))
	{
		return weapon;
	}
	
	return nullptr;
}

bool UStudentPerceptorMuylleFae::UseWeapon()
{
	bool hasShot = MyInventory->UseItem(weaponSlot);
	
	if (GetWeapon() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(5, 3.f, FColor::Red, 
	FString::Printf(TEXT("Tried shooting a zombie with a non existant gun")));
		return false;
	}
	
	if (GetWeapon()->GetValue() == 0)
	{
		MyInventory->RemoveItem(weaponSlot);
		
		if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
		{
			myController->GetBlackboardComponent()->SetValueAsObject(FName("MyWeapon"), nullptr);
		}
	}
	
	return hasShot;
}

void UStudentPerceptorMuylleFae::GrabItem(ABaseItem* item)
{
	int freeSlot = -1;
	
	for (int i {0}; i < MyInventory->GetInventory().Num()-1; i++)
	{
		if (MyInventory->GetInventory()[i] == nullptr)
		{
			freeSlot = i;
			break;
		}
	}
	
	if (auto healthKit = Cast<AMedkit>(item))
	{
		MyInventory->GrabItem(freeSlot, healthKit);
		
		if (SeenMedkits.Contains(healthKit))
		{
			SeenMedkits.Remove(healthKit);
		}
	}
	
	if (auto food = Cast<AFood>(item))
	{
		MyInventory->GrabItem(freeSlot, food);
		if (SeenFoods.Contains(food))
		{
			SeenFoods.Remove(food);
		}
	}
	
	if (auto weapon = Cast<AWeapon>(item))
	{
		if (SeenWeapons.Contains(weapon))
		{
			SeenWeapons.Remove(weapon);
		}
		MyInventory->GrabItem(weaponSlot, weapon);
		if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
		{
			myController->GetBlackboardComponent()->SetValueAsObject(FName("MyWeapon"), weapon);
			
		}
	}
	
	if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
	{
		myController->GetBlackboardComponent()->SetValueAsObject(FName("ItemToChase"), nullptr);
	}
}

void UStudentPerceptorMuylleFae::HouseChecked()
{
	CheckedHouses.Add(SeenHouses[SeenHouses.Num() - 1]);
	SeenHouses.RemoveAt(SeenHouses.Num() - 1);
	
	if (SeenHouses.Num() == 0)
	{
		if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
		{
			myController->GetBlackboardComponent()->SetValueAsObject(FName("HouseMiddle"), nullptr);
			
			if (myController->GetBlackboardComponent()->GetValueAsEnum(FName("SurvivorMode")) == 1)
			{
				return;
			}
			myController->GetBlackboardComponent()->SetValueAsEnum(FName("SurvivorMode"), 0);
			
		}
		return;
	}
	if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
	{
		myController->GetBlackboardComponent()->SetValueAsObject(FName("HouseMiddle"), SeenHouses[SeenHouses.Num() - 1]);
	}
}

void UStudentPerceptorMuylleFae::KilledEnemy(ABaseZombie* zombie)
{
	if (SeenZombies.Contains(zombie))
	{
		SeenZombies.Remove(zombie);
	}
	
	for (int i {0}; i < SeenZombies.Num(); i++)
	{
		if (!ZombieRangeCheck(SeenZombies[i]))
		{
			SeenZombies.RemoveAt(i);
		}
	}
	
	/*for (int i {0}; i < SeenZombies.Num(); i++)
	{
		ABaseZombie* nextZombie = SeenZombies[i];
	
		if (!IsValid(nextZombie))
		{
			SeenZombies.RemoveAt(i);
		}
	}*/
	
	if (SeenZombies.Num() == 0)
	{
		if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
		{
			myController->GetBlackboardComponent()->SetValueAsObject(FName("ZombieToRunFrom"), nullptr);
			
			if (SeenHouses.Num() > 0)
			{
				myController->GetBlackboardComponent()->SetValueAsEnum(FName("SurvivorMode"), 2);
				return;
			}
			myController->GetBlackboardComponent()->SetValueAsEnum(FName("SurvivorMode"), 0);
		}
		
		MySurvivorPawn->StopRunning();
		return;
	}
	
	ABaseZombie* nextZombie = SeenZombies[SeenZombies.Num()-1];
	if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
	{
		myController->GetBlackboardComponent()->SetValueAsObject(FName("ZombieToRunFrom"), nextZombie);
	}
}

bool UStudentPerceptorMuylleFae::HasInventorySpace()
{
	bool hasInventorySpace = false;
	
	for (int i {0}; i < MyInventory->GetInventory().Num()-1; i++)
	{
		if (MyInventory->GetInventory()[i] == nullptr)
		{
			hasInventorySpace = true;
			return hasInventorySpace;
		}
	}
	
	return false;
}

bool UStudentPerceptorMuylleFae::AnyGunsInMemory()
{
	if (SeenWeapons.Num() > 0)
	{
		return true;
	}
	
	return false;
}

bool UStudentPerceptorMuylleFae::AnyMedkitsInMemory()
{
	if (SeenMedkits.Num() > 0)
	{
		return true;
	}
	return false;
}

bool UStudentPerceptorMuylleFae::AnyFoodInMemory()
{
	if (SeenFoods.Num() > 0)
	{
		return true;
	}
	return false;
}

bool UStudentPerceptorMuylleFae::AnyFoodInInventory()
{
	bool hasFoodInInventory = false;
	
	for (auto item : MyInventory->GetInventory())
	{
		if (auto food = Cast<AFood>(item))
		{
			hasFoodInInventory = true;
			return hasFoodInInventory;
		}
	}
	
	return false;
}

bool UStudentPerceptorMuylleFae::AnyMedkitInInventory()
{
	bool hasMedkitInInventory = false;
	
	for (auto item : MyInventory->GetInventory())
	{
		if (auto medkit = Cast<AMedkit>(item))
		{
			hasMedkitInInventory = true;
			return hasMedkitInInventory;
		}
	}
	
	return false;
}

void UStudentPerceptorMuylleFae::UseMedkitInInventory()
{
	for (int i{0}; i < MyInventory->GetInventory().Num(); i++)
	{
		if (auto medkit = Cast<AMedkit>(MyInventory->GetInventory()[i]))
		{
			MyInventory->UseItem(i);
			
			if (medkit->GetValue() == 0)
			{
				MyInventory->RemoveItem(i);
			}
		}
	}
}

void UStudentPerceptorMuylleFae::UseFoodInInventory()
{
	for (int i{0}; i < MyInventory->GetInventory().Num(); i++)
	{
		if (auto medkit = Cast<AFood>(MyInventory->GetInventory()[i]))
		{
			MyInventory->UseItem(i);
			
			if (medkit->GetValue() == 0)
			{
				MyInventory->RemoveItem(i);
			}
		}
	}
}

void UStudentPerceptorMuylleFae::RemoveZombiesNotInRange()
{
	for (int i {0}; i < SeenZombies.Num(); i++)
	{
		if (!ZombieRangeCheck(SeenZombies[i]))
		{
			SeenZombies.RemoveAt(i);
		}
	}
	
	if (SeenZombies.Num() == 0)
	{
		if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
		{
			myController->GetBlackboardComponent()->SetValueAsObject(FName("ZombieToRunFrom"), nullptr);
			
			if (SeenHouses.Num() > 0)
			{
				myController->GetBlackboardComponent()->SetValueAsEnum(FName("SurvivorMode"), 2);
				return;
			}
			myController->GetBlackboardComponent()->SetValueAsEnum(FName("SurvivorMode"), 0);
		}
		
		MySurvivorPawn->StopRunning();
		return;
	}
	if (auto myController = Cast<ASurvivorAIController>(MySurvivorPawn->GetController()))
	{
		myController->GetBlackboardComponent()->SetValueAsObject(FName("ZombieToRunFrom"), SeenZombies[SeenZombies.Num()-1]);
	}
}

float UStudentPerceptorMuylleFae::GetStamina()
{
	return MyStamina->GetCurrentStamina();
}

float UStudentPerceptorMuylleFae::GetHealth()
{
	return MyHealth->GetHealth();
}
