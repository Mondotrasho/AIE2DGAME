// just does nothing
#ifndef IDLESTATE_H
#define IDLESTATE_H
#include "State.h"

class IdleState : public State {
public:
	IdleState() = default;
	virtual ~IdleState() = default;
	virtual void update(GameObject* gameObject, float deltaTime) {}
};
#endif // IDLESTATE_H
