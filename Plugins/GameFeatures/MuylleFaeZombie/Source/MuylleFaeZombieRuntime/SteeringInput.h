#pragma once

class SteeringInput
{
public:
	SteeringInput(FVector2D myPosition ,FVector2D target, float deltaTime);
	
	FVector2D Target;
	FVector2D MyPosition;
	
	float DeltaTime;
	
};
