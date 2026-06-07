#pragma once
#include <vector>

#include "SteeringBehaviour.h"

class UStudentPerceptorMuylleFae;

class AllEnemyAvoidance : public SteeringBehaviour
{
public:
	
	AllEnemyAvoidance(UStudentPerceptorMuylleFae* perceptor);
	
	
	
	virtual ~AllEnemyAvoidance();
	
	virtual SteeringOutput CalculateSteering(SteeringInput input) override;
	
private:
	UStudentPerceptorMuylleFae* MyPerceptor;
};

class Seek : public SteeringBehaviour
{
public:
	Seek() = default;
	virtual ~Seek() override = default;

	//Steering
	virtual SteeringOutput CalculateSteering(SteeringInput input) override;
};

class PathFollow : public SteeringBehaviour
{
public:
	PathFollow();
	virtual ~PathFollow() override;
	void SetPath(TArray<FVector>& path);
	virtual SteeringOutput CalculateSteering(SteeringInput input) override;

private:
	Seek* pSeek = nullptr;
	TArray<FVector> pathVec = {};
	int currentPathIndex = 0;

	void GotoNextPathPoint();
};