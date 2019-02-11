#pragma once
#include "Behaviour.h"
#include "SteeringForce.h"

class SteeringBehaviour :
	public Behaviour
{
public:
	SteeringBehaviour() = default;
	~SteeringBehaviour() = default;

	eBehaviourResult update(Agent* agent, float deltaTime) override;
	SteeringForce force;
};

