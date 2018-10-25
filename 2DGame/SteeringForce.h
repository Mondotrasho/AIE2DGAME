#pragma once
#include "Vector2.h"
#include "Agent.h"


class SteeringForce {

public:
	virtual ~SteeringForce() = default;

	virtual Vector2 getForce(Agent* agent) = 0;
};