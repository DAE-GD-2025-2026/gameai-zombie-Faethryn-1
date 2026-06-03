// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Common/InventoryComponent.h"
#include "Common/HealthComponent.h"
#include "Zombies/BaseZombie.h"
#include "Items/Medkit.h"
#include "Items/Food.h"
#include "Items/Weapon.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"
#include "StudentSurvivorLogic.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUYLLEFAEZOMBIERUNTIME_API UStudentSurvivorLogic : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStudentSurvivorLogic();
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UStudentPerceptorMuylleFae* MyPerceptor;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	ASurvivorPawn* MySurvivorPawn;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UInventoryComponent* MyInventory;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UHealthComponent* MyHealth;
	
	UPROPERTY(EditAnywhere, Category="Perception")
	UStaminaComponent* MyStamina;
	
	TSet<ABaseZombie*> SeenZombies;
	
	TSet<AFood*> SeenFoods;
	
	TSet<AMedkit*> SeenMedkits;
	
	TSet<AWeapon*> SeenWeapons;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnPerceptionHappened(AActor* perceivedActor, FAIStimulus stimulus);
	
};
