
#include "SteeringBehavioursFaeMuylle.h"

#include "SteeringInputFaeMuylle.h"
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

SteeringOutputFaeMuylle AllEnemyAvoidance::CalculateSteering(SteeringInputFaeMuylle input)
{
	SteeringOutputFaeMuylle output;
	
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

SteeringOutputFaeMuylle Seek::CalculateSteering(SteeringInputFaeMuylle input)
{
	SteeringOutputFaeMuylle Steering{};

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

SteeringOutputFaeMuylle PathFollow::CalculateSteering(SteeringInputFaeMuylle input)
{
	if (pathVec.Num() == 0)
	{
		return SteeringOutputFaeMuylle{};
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

	SteeringInputFaeMuylle myInput{input.MyPosition, FVector2D{pathVec[currentPathIndex].X, pathVec[currentPathIndex].Y}, input.DeltaTime};
	
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
		
		SteeringOutputFaeMuylle output{};
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


