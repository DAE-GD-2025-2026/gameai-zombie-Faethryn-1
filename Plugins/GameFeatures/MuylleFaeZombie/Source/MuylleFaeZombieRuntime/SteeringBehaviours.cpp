
#include "SteeringBehaviours.h"

#include "SteeringInput.h"
#include "StudentPerceptorMuylleFae.h"
#include "Survivor/SurvivorPawn.h"
#include "Zombies/BaseZombie.h"

AllEnemyAvoidance::AllEnemyAvoidance(UStudentPerceptorMuylleFae* perceptor)
	:
MyPerceptor{perceptor}
{
}

AllEnemyAvoidance::~AllEnemyAvoidance()
{
}

SteeringOutput AllEnemyAvoidance::CalculateSteering(SteeringInput input)
{
	SteeringOutput output;
	
	FVector2D averagedEnemyPositions = FVector2D::ZeroVector;
	
	if (MyPerceptor->SeenZombies.Num() == 0)
	{
		return output;
	}
	
	for (auto enemy : MyPerceptor->SeenZombies)
	{
		FVector position = enemy->GetActorLocation();
		
		averagedEnemyPositions += FVector2D{position.X, position.Y};
	}
	
	averagedEnemyPositions /= MyPerceptor->SeenZombies.Num();
	FVector myPawnPosition = MyPerceptor->MySurvivorPawn->GetActorLocation();
	FVector2D directionToRun = FVector2D{myPawnPosition.X, myPawnPosition.Y} - averagedEnemyPositions;
	
	directionToRun.Normalize();
	
	output.Velocity = directionToRun;
	return output;
}

SteeringOutput Seek::CalculateSteering(SteeringInput input)
{
	SteeringOutput Steering{};

	FVector2D targetDirection = input.Target - input.MyPosition;

	targetDirection.Normalize();

	Steering.Velocity = targetDirection;

	return Steering;
}

PathFollow::PathFollow()
{
	pSeek = new Seek();
	pathVec.Add(FVector{0,0,0});
}

PathFollow::~PathFollow()
{
	delete pSeek;
}

void PathFollow::SetPath(TArray<FVector>& path)
{
	pathVec = path;  
	
	currentPathIndex = -1;
	GotoNextPathPoint();
	
	
}

SteeringOutput PathFollow::CalculateSteering(SteeringInput input)
{
	if (pathVec.Num() == 0)
	{
		return SteeringOutput{};
	}
	if (currentPathIndex < pathVec.Num() -1)
	{
		float agentRadius = 5;
		FVector2D ToPathPoint{FVector2D{pathVec[currentPathIndex].X, pathVec[currentPathIndex].Y} - input.MyPosition};
		
		if (ToPathPoint.SizeSquared() < agentRadius * agentRadius)
		{
			//Reached point of the path
			GotoNextPathPoint();
		}
	}

	SteeringInput myInput{input.MyPosition, FVector2D{pathVec[currentPathIndex].X, pathVec[currentPathIndex].Y}, input.DeltaTime};
	
	if (currentPathIndex == pathVec.Num() - 1)
	{
		float distance = FVector2D::Distance(input.MyPosition, input.Target);
		
		float ratio =  distance / 100;
		
		if (ratio > 1)
		{
			ratio = 1;
		}
		
		FVector2D targetDirection = input.Target - input.MyPosition;

		targetDirection.Normalize();
		
		targetDirection *= ratio;
		
		SteeringOutput output{};
		output.Velocity = targetDirection;
		return output;
	}
	
	return pSeek->CalculateSteering(myInput);
	
	//return SteeringOutput{};
}

void PathFollow::GotoNextPathPoint()
{
	++currentPathIndex;
	if (currentPathIndex >= pathVec.Num()) return;
}


