#include "SteeringForce.h"



SteeringForce::SteeringForce()
{
}


SteeringForce::~SteeringForce()
{
}

Vector2 SteeringForce::getforce(AutonomousAgent* agent)
{
	return agent->GetMaxforce();
}
