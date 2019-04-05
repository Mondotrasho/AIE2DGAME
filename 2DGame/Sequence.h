#pragma once
#include "Composite.h"

//A Sequence acts as an AND
class Sequence :
	public Composite
{
public:
	Sequence(){};
	~Sequence(){};

	eBehaviourResult execute(GameObject* agent, float deltaTime) override;;
};

inline eBehaviourResult Sequence::execute(GameObject* agent, float deltaTime)
{
	for (auto child : children)
	{
		auto result = child->execute(agent, deltaTime);
		if (result == FAILURE)
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

