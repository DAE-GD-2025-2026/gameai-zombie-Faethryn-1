#pragma once

class SteeringInputFaeMuylle;

class SteeringOutputFaeMuylle
{
public:
	
	SteeringOutputFaeMuylle() = default;
	
	FVector2D Velocity{ FVector2D(0, 0) };
	
	bool IsValid{ true };
	
};
