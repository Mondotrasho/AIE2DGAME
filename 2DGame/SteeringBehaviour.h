#pragma once
#include "Behaviour.h"
#include "SteeringForce.h"

class SteeringBehaviour :
	public Behaviour
{
public:
	SteeringBehaviour() = default;
	~SteeringBehaviour() = default;

	Vector2 update(Object* agent, float deltaTime) override;
	SteeringForce force;
};

