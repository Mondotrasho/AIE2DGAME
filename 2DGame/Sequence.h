#pragma once
#include "Composite.h"
class Sequence :
	public Composite
{
public:
	Sequence();
	~Sequence();

	eBehaviourResult execute(GameObject* agent, float deltaTime) override
	{
		for (auto child : children)
		{
			if (child->execute(agent,deltaTime) == FAILURE)
			{
				return FAILURE;
			}
			return SUCCESS;
		}
	};
};

