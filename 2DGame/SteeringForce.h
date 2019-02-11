#pragma once
#include "VelocityAgent.h"

class SteeringForce
{
public:
	SteeringForce();
	virtual ~SteeringForce();

	virtual Vector2 getForce(VelocityAgent agent);
};

