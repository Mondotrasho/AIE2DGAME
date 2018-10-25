#ifndef CONDITION_H
#define CONDITION_H

#include "IBehaviour.h"

class Condition : public IBehaviour {
public:

	Condition() {}
	virtual ~Condition() {}

	virtual bool test(Agent* agent) const = 0;

	eBehaviourResult update(Agent* agent, float deltaTime) override
	{
		if (test(agent))
			return eBehaviourResult::SUCCESS;
		return eBehaviourResult::FAILURE;
	}
};
#endif // CONDITION_H
