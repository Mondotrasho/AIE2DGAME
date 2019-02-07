#include "FollowBehaviour.h"
#include "Input.h"
#include "Vector2.h"
#include "Agent.h"


FollowBehaviour::FollowBehaviour()
{
}


FollowBehaviour::~FollowBehaviour()
{
}

eBehaviourResult FollowBehaviour::update(Agent* agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	Vector2 mousePos = { 
		static_cast<float>(input->getMouseX()) ,
		static_cast<float>(input->getMouseY()) };
	
	Vector2 pos = agent->get_position();
	
	Vector2 dir = pos - mousePos;
	float distance = dir.magnitude();

	if (distance > 0)
	{
		dir = dir.normalised();

		agent->set_position(pos - dir * deltaTime * 50.0f);
	}

	return eBehaviourResult::SUCCESS;

	//Function execute
	//	If the target is invalid, return eBehaviourResult::FAILURE
	//	Get the coordinates of the target agent
	//	Get this agent’s coordinates
	//	Calculate the distance between the two agents
	//	If the distance is greater than 0 then
	//	Get the vector describing the direction of the target and normalize it
	//	Move this agent in this direction at the agent’s maximum speed
	//	return eBehaviourResult::SUCCESS
}
