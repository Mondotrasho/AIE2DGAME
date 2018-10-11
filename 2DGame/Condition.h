#ifndef CONDITION_H
#define CONDITION_H

#include "IBehaviour.h"

class Condition : public IBehaviour {
public:
	Condition() {}
	virtual ~Condition() {}
	virtual bool test(GameObject* gameObject) const = 0;
	virtual eBehaviourResult update(GameObject* gameObject, float deltaTime) {
		if (test(gameObject))
			return eBehaviourResult::SUCCESS;
		return eBehaviourResult::FAILURE;
	}
};
#endif // CONDITION_H
