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
			auto result = child->execute(agent, deltaTime);
			if (result == SUCCESS)
			{
				return SUCCESS;
			}
			if (result == RUNNING)
			{
				return RUNNING;
			}
		}
		return FAILURE;
	}
};

