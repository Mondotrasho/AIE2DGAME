#include "Selector.h"



Selector::Selector()
{
}


Selector::~Selector()
{
}

eBehaviourResult Selector::execute(GameObject* agent, float deltaTime)
{
	for (auto child : children)
	{
		if (child->execute(agent, deltaTime) == SUCCESS)
		{
			return SUCCESS;
		}
		return FAILURE;
	}
}
