#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Transition.h"

class GameObject;
class Transition;

class State
{
public:
	State() {};
	virtual ~State() {}
	virtual void update(GameObject* agent, float deltaTime) = 0;
	virtual void init(GameObject* agent) {};
	virtual void exit(GameObject* agent) {};

	void addTransition(Transition* transition) {
		m_transitions.push_back(transition);
	}

	Transition* getTriggeredTransition(GameObject* gameObject);

protected:
	std::vector<Transition*> m_transitions;
};

inline Transition* State::getTriggeredTransition(GameObject* gameObject)
{
	for (auto transition : m_transitions) {
		if (transition->hasTriggered(gameObject))
			return transition;
	}
	return nullptr;
}

#endif // STATE_H
