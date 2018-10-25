#include "FollowBehaviour.h"
#include "Input.h"
#include "GameObject.h"
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

	
	auto mouseX = input->getMouseX();
	auto mouseY = input->getMouseY();
	Vector2 mousePos = { static_cast<float>(mouseX) , static_cast<float>(mouseY) };
	
	Vector2 agentpos =  agent->getPosition();
	
	Vector2 dir = agentpos - mousePos;
	float distance = dir.magnitude();

	if (distance > 0)
	{
		dir = dir.normalised();

		auto temp = agentpos - dir * deltaTime * 50.0f;

		agent->setPosition(temp);
	}

	return eBehaviourResult::SUCCESS;

	//Function update

	//	If the target is invalid, return eBehaviourResult::FAILURE
	//	Get the coordinates of the target agent
	//	Get this agent’s coordinates
	//	Calculate the distance between the two agents
	//	If the distance is greater than 0 then
	//	Get the vector describing the direction of the target and normalize it
	//	Move this agent in this direction at the agent’s maximum speed
	//	return eBehaviourResult::SUCCESS
}
