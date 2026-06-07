#pragma once

class SteeringInput;

class SteeringOutput
{
public:
	
	SteeringOutput() = default;
	
	FVector2D Velocity{ FVector2D(0, 0) };
	
	bool IsValid{ true };
	
};
