#pragma once
#include "Behaviour.h"
#include "NavMesh.h"
#include "GameObject.h"

//CheckIfInRangeOfTarget


class CheckIfInRangeOfTarget : public Behaviour
{
public:
	CheckIfInRangeOfTarget()
	{
	}

	CheckIfInRangeOfTarget(float newrange) : range(newrange) {}

	~CheckIfInRangeOfTarget()
	{
	}


	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		//todo remove when I can move in nodes
		//if(gameObject->target->Occupied == gameObject->Occupied)
		//{
		//	return SUCCESS;
		//}
		if (gameObject->target->position.distance(gameObject->position) < range)
		{
			return SUCCESS;
		}
		return FAILURE;
	}

	float range;
};