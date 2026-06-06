// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "StudentPerceptorMuylleFae.generated.h"

class ABaseItem;
class AHouse;
class ASurvivorPawn;
class UInventoryComponent;
class UHealthComponent;
class UStaminaComponent;
class AFood;
class AMedkit;
class AWeapon;
class ABaseZombie;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MUYLLEFAEZOMBIERUNTIME_API UStudentPerceptorMuylleFae : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStudentPerceptorMuylleFae();
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	ASurvivorPawn* MySurvivorPawn;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UInventoryComponent* MyInventory;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UHealthComponent* MyHealth;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UStaminaComponent* MyStamina;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	float ZombieRunRange{5000.0f};
	
	TArray<ABaseZombie*> SeenZombies;
	
	TArray<AFood*> SeenFoods;
	
	TArray<AMedkit*> SeenMedkits;
	
	TArray<AWeapon*> SeenWeapons;
	
	TArray<AHouse*> SeenHouses;
	
	TArray<AHouse*> CheckedHouses;
	
	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	bool ZombieRangeCheck(ABaseZombie* zombieToCheck);
	
	void SurvivorSawZombieInRange(ABaseZombie* zombie);
	
	void SawFood(AFood* food);
	
	void SawMedkit(AMedkit* medkit);
	
	void SawWeapon(AWeapon* weapon);
	
	void SawHouse(AHouse* house);
	
	bool HasWeapon();
	
	AWeapon* GetWeapon();
	
	bool UseWeapon();
	
	const int weaponSlot{4};
	
	void GrabItem(ABaseItem* item);
	
	void HouseChecked();
	
	void KilledEnemy(ABaseZombie* zombie);
	
	bool HasInventorySpace();
	
	UFUNCTION(BlueprintCallable)
	float GetStamina();
	
	UFUNCTION(BlueprintCallable)
	float GetHealth();
};
