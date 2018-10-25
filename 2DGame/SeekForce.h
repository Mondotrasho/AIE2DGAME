#pragma once
#include "SteeringForce.h"


class SeekForce : SteeringForce
{
public:
	SeekForce(Agent* agent) : m_target(agent) {};

	virtual ~SeekForce();

	Vector2 getForce(Agent* agent) override;

private:
	Agent * m_target;

};

inline Vector2 SeekForce::getForce(Agent* agent)
{
	Vector2 targetVelocity = (m_target->getPosition() - agent->getPosition().normalised()) * agent->maxVelocity;
}
