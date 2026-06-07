#pragma once
#include "SteeringOutput.h"


class SteeringBehaviour
{
public:
	SteeringBehaviour() = default;
	virtual ~SteeringBehaviour() = default;

	virtual SteeringOutput CalculateSteering(SteeringInput input) = 0;
	
};
