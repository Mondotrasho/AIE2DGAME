#pragma once

#include "IBehaviour.h"
#include "Agent.h"
#include "SteeringForce.h"

class SteeringBehaviour : IBehaviour
{
public:
	SteeringBehaviour();
	virtual ~SteeringBehaviour() {}

	eBehaviourResult update(Agent* agent, float deltaTime) override;;

private:
 	SteeringForce m_steeringForce;
};

inline eBehaviourResult SteeringBehaviour::update(Agent* agent, float deltaTime)
{
	if (m_steeringForce)
	{
		agent->AddForce(m_steeringForce->getForce(agent));
	}


	return eBehaviourResult::SUCCESS;
}
