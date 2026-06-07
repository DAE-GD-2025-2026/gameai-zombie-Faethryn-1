#pragma once
#include "SteeringOutputFaeMuylle.h"


class SteeringBehaviourFaeMuylle
{
public:
	SteeringBehaviourFaeMuylle() = default;
	virtual ~SteeringBehaviourFaeMuylle() = default;

	virtual SteeringOutputFaeMuylle CalculateSteering(SteeringInputFaeMuylle input) = 0;
	
};
