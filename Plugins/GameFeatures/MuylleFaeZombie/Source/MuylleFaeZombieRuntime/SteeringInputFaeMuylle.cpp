
#include "SteeringInputFaeMuylle.h"

SteeringInputFaeMuylle::SteeringInputFaeMuylle(FVector2D myPosition ,FVector2D target, float deltaTime)
	:
DeltaTime{deltaTime},
Target(target),
MyPosition{myPosition}
{
	
}
