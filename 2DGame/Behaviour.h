#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H
#include "GameObject.h"

enum eBehaviourResult {
	SUCCESS,
	FAILURE,
	RUNNING
};
class Behaviour {
public:
	// empty constructors and destructors for base class
	Behaviour() = default;
	virtual ~Behaviour() = default;
	// pure virtual function for executing the behaviour
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime) = 0;
};
#endif // BEHAVIOUR_H
