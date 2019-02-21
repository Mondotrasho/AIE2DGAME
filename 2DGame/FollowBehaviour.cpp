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

Vector2 FollowBehaviour::update(Object* agent, float deltaTime)
{
	Vector2 dir =  m_target->pos - agent->get_position();
	float distance = dir.magnitude();

	if (distance > 0.1f)
	{
		return dir.normalised();
	}

	return Vector2(0, 0);

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
