#include "FiniteStateMachine.h"
#include "State.h"

FiniteStateMachine::FiniteStateMachine(int stateCount) 
{
	m_states.resize(stateCount);
}

FiniteStateMachine::~FiniteStateMachine() 
{
	for (auto state : m_states) 
		delete state;
}

void FiniteStateMachine::addState(int id, State* newState) 
{
	m_states[id] = newState;
}

void FiniteStateMachine::forceState(int id) 
{
	m_currentState = m_states[id]; 
}

void FiniteStateMachine::update(GameObject * gameObject, float deltaTime) 
{
	if (m_currentState != nullptr) 
	{
		m_currentState->onUpdate(gameObject, deltaTime);
		State* next = m_currentState->getNextState(gameObject);

		if (next != m_currentState && next != nullptr)
		{
			m_currentState->onExit(gameObject);
			m_currentState = next;
			m_currentState->onEnter(gameObject);
		}
	}
}
