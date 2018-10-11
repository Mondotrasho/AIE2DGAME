#include "FollowBehaviour.h"
#include "Input.h"
#include "GameObject.h"
#include "Vector2.h"


FollowBehaviour::FollowBehaviour()
{
}


FollowBehaviour::~FollowBehaviour()
{
}

eBehaviourResult FollowBehaviour::update(GameObject* gameObject, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	float x = 0, y = 0;
	auto mouseX = input->getMouseX();
	auto mouseY = input->getMouseY();
	Vector2 mousePos = { static_cast<float>(mouseX) , static_cast<float>(mouseY) };
	gameObject->getPosition(&x, &y);
	Vector2 pos = { x,y };
	Vector2 dir = pos - mousePos;
	float distance = dir.magnitude();

	if (distance > 0)
	{
		dir = dir.normalised();

		auto temp = pos - dir * deltaTime * 50.0f;

		gameObject->setPosition(temp.x, temp.y);
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
