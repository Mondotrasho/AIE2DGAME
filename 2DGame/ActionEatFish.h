#pragma once
#include "GameObject.h"


class ActionEatFish : public Behaviour
{
public:
	ActionEatFish()
	{
	}

	~ActionEatFish()
	{
	}


	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		gameObject->size += gameObject->target->size;
		gameObject->target->remove();
		gameObject->target = nullptr;
		return SUCCESS;
	}
};
