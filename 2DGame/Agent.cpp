#include "Agent.h"



Agent::Agent()
{
}

void Agent::AddBehaviour(Behaviour* behaviour)
{
	m_BehaviourList.push_back(behaviour);
}

void Agent::Update(float deltaTime)
{
	//sense(deltaTime);
	//think(deltaTime);
	//act(deltaTime);
	for (auto behave : m_BehaviourList)
	{
		behave->update(this, deltaTime);
	}
}
