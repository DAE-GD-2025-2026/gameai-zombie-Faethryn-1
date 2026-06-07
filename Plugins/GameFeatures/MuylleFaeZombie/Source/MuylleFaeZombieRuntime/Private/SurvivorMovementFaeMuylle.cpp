// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorMovementFaeMuylle.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "MuylleFaeZombieRuntime/SteeringBehavioursFaeMuylle.h"
#include "MuylleFaeZombieRuntime/SteeringInputFaeMuylle.h"
#include "MuylleFaeZombieRuntime/StudentPerceptorMuylleFae.h"
#include "Survivor/SurvivorPawn.h"

// Sets default values for this component's properties
USurvivorMovementFaeMuylle::USurvivorMovementFaeMuylle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

USurvivorMovementFaeMuylle::~USurvivorMovementFaeMuylle()
{
	delete pEnemyAvoidance;
	delete pPathFollowBehaviour;
}


// Called when the game starts
void USurvivorMovementFaeMuylle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	FloatingPawnMovement = GetOwner()->GetComponentByClass<UFloatingPawnMovement>();
	pEnemyAvoidance = new AllEnemyAvoidance(GetOwner()->GetComponentByClass<UStudentPerceptorMuylleFae>());
	
	MyPawn = Cast<ASurvivorPawn>(GetOwner());
	pPathFollowBehaviour = new PathFollow();
	
	ApplyTargetPosition(GetOwner()->GetActorLocation());
}


// Called every frame
void USurvivorMovementFaeMuylle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ApplyMovement(DeltaTime);
	// ...
}


void USurvivorMovementFaeMuylle::ApplyTargetPosition(FVector targetPosition)
{
	ASurvivorPawn* myPawn = Cast<ASurvivorPawn>(GetOwner());
	
	TArray<FVector> pathVec = myPawn->CalculatePath(targetPosition);
	
	DebugDrawPath(pathVec);
	pPathFollowBehaviour->SetPath(pathVec);
	
	TargetPosition = targetPosition;
	
	IsGoingSomeWhere = true;
}

void USurvivorMovementFaeMuylle::DoneMovingToPoint()
{
	IsGoingSomeWhere = false;
}

void USurvivorMovementFaeMuylle::ApplyMovement(float deltaTime)
{
	FVector myPosition = GetOwner()->GetActorLocation();
	SteeringInputFaeMuylle input{FVector2D{myPosition.X, myPosition.Y}, FVector2D{TargetPosition.X, TargetPosition.Y}, deltaTime };
	
	FVector2D movement = FVector2D::ZeroVector;
	
	if (IsGoingSomeWhere)
	{
		movement += pPathFollowBehaviour->CalculateSteering(input).Velocity;
		
	}
	movement += pEnemyAvoidance->CalculateSteering(input).Velocity;
	
	MyPawn->AddMovementInput(FVector{movement.X, movement.Y, 0});
	
	movement *= 10;
	
	DrawDebugLine(GetWorld(), myPosition, myPosition + FVector{movement.X, movement.Y, 0}, FColor::Green, false, 10.f,0, 10);
}

void USurvivorMovementFaeMuylle::DebugDrawPath(TArray<FVector> path)
{
	for (int i = 0; i < path.Num() -1; i++)
	{
		int current = i;
		int next = i +1;
		
		FVector currentPosition = path[current];
		FVector nextPosition = path[next];
		
		DrawDebugLine(GetWorld(), currentPosition, nextPosition, FColor::Red, false, 10.f,0, 10);
	}
}

