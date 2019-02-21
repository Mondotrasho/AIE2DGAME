#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H
#include "Vector2.h"

class Object;

enum eBehaviourResult {
	SUCCESS,
	FAILURE,
	RUNNING
};

// a behaviour in this context is an action generally a movement one
class Behaviour {
public:

	// empty constructors and destructors for base class
	Behaviour() = default;
	virtual ~Behaviour() = default;

	// pure virtual function for executing the behaviour
	virtual Vector2 update(Object* agent, float deltaTime) = 0;
};
#endif // BEHAVIOUR_H
