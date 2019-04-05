#pragma once
#include "GameObject.h"


class ActionEatFood : public Behaviour
{
public:
	ActionEatFood()
	{
	}
	~ActionEatFood()
	{
	}


	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		gameObject->size++;

		if (gameObject->target != nullptr) {
			gameObject->target->remove();		
			gameObject->target = nullptr;
		}
		return SUCCESS;
	}
;
};
