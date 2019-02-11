#include "SteeringBehaviour.h"
#include "VelocityAgent.h"


eBehaviourResult SteeringBehaviour::update(Agent* agent, float deltaTime)
{
	//update(agent, deltaTime);
	agent->set_velocity(Vector2(1,0));
	auto a = agent->get_velocity();
	return SUCCESS;
}
