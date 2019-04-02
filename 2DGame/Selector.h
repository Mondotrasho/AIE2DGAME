#pragma once
#include "Composite.h"

//A Selector acts as an OR
class Selector :
	public Composite
{
public:
	Selector();
	~Selector();
	eBehaviourResult execute(GameObject* agent, float deltaTime) override 
	{
		for (auto child : children)
		{
			if (child->execute(agent, deltaTime) == SUCCESS)
			{
				return SUCCESS;
			}
			if (child->execute(agent, deltaTime) == RUNNING)
			{
				return RUNNING;
			}
		}
		return FAILURE;
	}
};

