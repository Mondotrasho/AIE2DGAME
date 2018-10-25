#ifndef TRANSITION_H
#define TRANSITION_H

#include "Condition.h"

class State;
class GameObject;

class Transition {
public:
	Transition(State* target, Condition* condition) : m_target(target),m_condition(condition) {}

	~Transition() {}

	State* getTargetState() { return m_target; }

	bool hasTriggered(GameObject* gameObject) {	return m_condition->test(gameObject);}

private:
	State* m_target;
	Condition* m_condition;
};
#endif // TRANSITION_H
