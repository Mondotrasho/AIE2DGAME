#include "SteeringForce.h"



SteeringForce::SteeringForce()
{
}


SteeringForce::~SteeringForce()
{
}

Vector2 SteeringForce::getForce(VelocityAgent agent)
{
	return agent.GetMaxforce();
}
