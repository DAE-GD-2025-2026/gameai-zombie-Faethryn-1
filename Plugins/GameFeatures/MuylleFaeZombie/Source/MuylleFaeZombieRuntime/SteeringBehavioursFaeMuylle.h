#pragma once
#include <vector>

#include "SteeringBehaviourFaeMuylle.h"
#include "SteeringOutputFaeMuylle.h"

class UStudentPerceptorMuylleFae;

class AllEnemyAvoidance : public SteeringBehaviourFaeMuylle
{
public:
	
	AllEnemyAvoidance(UStudentPerceptorMuylleFae* perceptor);
	
	
	
	virtual ~AllEnemyAvoidance();
	
	virtual SteeringOutputFaeMuylle CalculateSteering(SteeringInputFaeMuylle input) override;
	
private:
	UStudentPerceptorMuylleFae* MyPerceptor;
};

class Seek : public SteeringBehaviourFaeMuylle
{
public:
	Seek() = default;
	virtual ~Seek() override = default;

	//Steering
	virtual SteeringOutputFaeMuylle CalculateSteering(SteeringInputFaeMuylle input) override;
};

class PathFollow : public SteeringBehaviourFaeMuylle
{
public:
	PathFollow();
	virtual ~PathFollow() override;
	void SetPath(TArray<FVector>& path);
	virtual SteeringOutputFaeMuylle CalculateSteering(SteeringInputFaeMuylle input) override;

private:
	Seek* pSeek = nullptr;
	TArray<FVector> pathVec = {};
	int currentPathIndex = 0;

	void GotoNextPathPoint();
};