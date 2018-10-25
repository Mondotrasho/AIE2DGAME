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
	virtual void update(Agent* agent, float deltaTime) = 0;
	virtual void init(Agent* agent) {};
	virtual void exit(Agent* agent) {};

	void addTransition(Transition* transition) {
		m_transitions.push_back(transition);
	}

	Transition* getTriggeredTransition(Agent* agent);

protected:
	std::vector<Transition*> m_transitions;
};

inline Transition* State::getTriggeredTransition(Agent* agent)
{
	for (auto transition : m_transitions) {
		if (transition->hasTriggered(agent))
			return transition;
	}
	return nullptr;
}

#endif // STATE_H
