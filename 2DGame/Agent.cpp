#include "Agent.h"
#include "Renderer2D.h"


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

	if (velocity.x < Maxvelocity.x)
		velocity.x = Maxvelocity.x;

	if (velocity.y < Maxvelocity.y)
		velocity.y = Maxvelocity.y;

	set_position(get_position() + velocity);
}

void Agent::draw(aie::Renderer2D* renderer)
{
	renderer->drawCircle(m_Position.x, m_Position.y, dotSize);
}

void Agent::add_force(Vector2 force)
{
	velocity += force;
}