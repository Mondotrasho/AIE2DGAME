#pragma once
#include "Behaviour.h"
#include "GameObject.h"

class CheckBeingHunted : public Behaviour
{
public:
	CheckBeingHunted()
	{
	}

	CheckBeingHunted(float newrange) : range(newrange) {}

	~CheckBeingHunted()
	{
	}

	//todo run from closest
	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		for (auto obj : *gameObject->ObjectPool)
		{
			if(obj->target == gameObject && gameObject->position.distance(obj->position) < range)
			{
				gameObject->hunter = obj;
				return SUCCESS;
			}
		}
		return FAILURE;
	}

	float range;
};
