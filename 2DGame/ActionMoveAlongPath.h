#pragma once
#include "Behaviour.h"
#include "GameObject.h"

class ActionMoveAlongPath :
	public Behaviour
{
public:
	ActionMoveAlongPath();
	~ActionMoveAlongPath();

	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		if (gameObject->smoothPath.empty())
			return SUCCESS;

		// access first node we're heading towards
		Vector2 first = gameObject->smoothPath.front();

		// distance to first
		float xDiff = first.x - gameObject->position.x;
		float yDiff = first.y - gameObject->position.y;

		float distance = xDiff * xDiff + yDiff * yDiff;

		// if not at the target then move towards it
		if (distance > 25) {

			distance = sqrt(distance);
			xDiff /= distance;
			yDiff /= distance;

			// move to target (can overshoot!)
			gameObject->position.x += xDiff * gameObject->speed * deltaTime;
			gameObject->position.y += yDiff * gameObject->speed * deltaTime;
		}
		else {
			// at the node, remove it and move to the next
			gameObject->smoothPath.pop_front();
			gameObject->path.pop_front();
		}
		return RUNNING;
	}
};

