// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivorMovement.generated.h"


class ASurvivorPawn;
class AllEnemyAvoidance;
class PathFollow;
class UFloatingPawnMovement;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MUYLLEFAEZOMBIERUNTIME_API USurvivorMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USurvivorMovement();
	
	virtual ~USurvivorMovement() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyTargetPosition(FVector targetPosition);
	
	UFUNCTION(BlueprintCallable)
	void DoneMovingToPoint();

private:
	UFloatingPawnMovement* FloatingPawnMovement;
	
	ASurvivorPawn* MyPawn;
	
	FVector TargetPosition;
	
	PathFollow* pPathFollowBehaviour = nullptr;
	
	AllEnemyAvoidance* pEnemyAvoidance = nullptr;
	
	void ApplyMovement(float deltaTime);
	
	void DebugDrawPath(TArray<FVector> path);
	
	bool IsGoingSomeWhere = false;
};
