#pragma once

class SteeringInputFaeMuylle
{
public:
	SteeringInputFaeMuylle(FVector2D myPosition ,FVector2D target, float deltaTime);
	
	FVector2D Target;
	FVector2D MyPosition;
	
	float DeltaTime;
	
};
