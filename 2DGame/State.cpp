#include "State.h"
#include "Transition.h"

State::State()
{
}

State::~State()
{
	for (auto t : m_transitions) 
		delete t;
}

void State::addTransition(Transition* transition) 
{
	m_transitions.push_back(transition);
}

State* State::getNextState(GameObject* gameObject) 
{
	for (auto transition : m_transitions) 
	{
		if (transition->isConditionMet(gameObject))
			return transition->getTargetState();
	}
	// no state change
	return nullptr;
}
