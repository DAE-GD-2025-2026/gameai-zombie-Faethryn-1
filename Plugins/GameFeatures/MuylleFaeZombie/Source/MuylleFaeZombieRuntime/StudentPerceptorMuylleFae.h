// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "StudentPerceptorMuylleFae.generated.h"

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
	
	UPROPERTY(EditAnywhere, Category="Perception")
	ASurvivorPawn* MySurvivorPawn;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UInventoryComponent* MyInventory;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UHealthComponent* MyHealth;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UStaminaComponent* MyStamina;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	float ZombieRunRange{500.0f};
	
	TSet<ABaseZombie*> SeenZombies;
	
	TSet<AFood*> SeenFoods;
	
	TSet<AMedkit*> SeenMedkits;
	
	TSet<AWeapon*> SeenWeapons;
	
	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	bool ZombieRangeCheck(ABaseZombie* zombieToCheck);
	
	void SurvivorSawZombieInRange(ABaseZombie* zombie);
	
};
