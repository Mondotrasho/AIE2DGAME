#pragma once
#include "GameObject.h"
#include "Vector2.h"

class Agent : public GameObject {
public:
	Agent() = default;
	virtual ~Agent() = default;


	Vector2 Position;
	Vector2 Velocity;
	float Acceleration;
	float Force;

	virtual void update(float deltaTime);

	void AddForce(float addMe);
};

inline void Agent::update(float deltaTime)
{
	Position = Position + Velocity * deltaTime;
}

inline void Agent::AddForce(float addMe)
{
	Acceleration += addMe;
}

