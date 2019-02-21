#pragma once
#include "AutonomousAgent.h"
#include "Object.h"

class SteeringForce
{
public:
	SteeringForce();
	virtual ~SteeringForce();

	Vector2 getforce(AutonomousAgent* agent);
};

