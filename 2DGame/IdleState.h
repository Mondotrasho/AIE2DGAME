// just does nothing
#ifndef IDLESTATE_H
#define IDLESTATE_H
#include "State.h"

class IdleState : public State {
public:

	IdleState() = default;
	virtual ~IdleState() = default;

	void update(Agent* agent, float deltaTime) override {}
};
#endif // IDLESTATE_H
