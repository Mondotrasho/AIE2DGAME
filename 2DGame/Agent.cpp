#include "Agent.h"



Agent::Agent()
{
}

void Agent::add_behaviour(Behaviour* behaviour)
{
	m_BehaviourList.push_back(behaviour);
}

void Agent::update(float deltaTime)
{
	//sense(deltaTime);
	//think(deltaTime);
	//act(deltaTime);
	for (auto behave : m_BehaviourList)
	{
		behave->update(this, deltaTime);
	}
}
