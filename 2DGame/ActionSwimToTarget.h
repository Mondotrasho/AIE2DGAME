#pragma once
#pragma once
#include "Behaviour.h"
#include "GameObject.h"
#include "Utilities.h"

class ActionSwimToTarget :
	public Behaviour
{
public:
	ActionSwimToTarget(){}
	~ActionSwimToTarget(){}

	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override;
};

inline eBehaviourResult ActionSwimToTarget::execute(GameObject* gameObject, float deltaTime)
{
	// distance to first
	float xDiff = gameObject->target->position.x - gameObject->position.x;
	float yDiff = gameObject->target->position.y - gameObject->position.y;

	float distance = xDiff * xDiff + yDiff * yDiff;

	// if not at the target then move towards it
	if (distance > 1)
	{
		distance = sqrt(distance);
		xDiff /= distance;
		yDiff /= distance;

		// move to target (can overshoot!)
		gameObject->position.x += xDiff * gameObject->speed * deltaTime;
		gameObject->position.y += yDiff * gameObject->speed * deltaTime;

		auto dir = gameObject->position - gameObject->target->position;
		auto angle = Vector2(0, 1).angle_between(dir);

		if (gameObject->position.x < gameObject->target->position.x)
		{
			gameObject->angle = angle;
		}
		if (gameObject->position.x > gameObject->target->position.x)
		{
			gameObject->angle = -angle;
		}
		return RUNNING;
	}
	return SUCCESS;
}

