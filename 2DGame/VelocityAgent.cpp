#include "VelocityAgent.h"
#include "Renderer2D.h"


VelocityAgent::VelocityAgent()
{
}

void VelocityAgent::update(float deltatime)
{
	for (auto behaviour : m_BehaviourList)
	{
		behaviour->update(this, deltatime);
	}

	if (velocity.x < Maxvelocity.x)
		velocity.x = Maxvelocity.x;

	if (velocity.y < Maxvelocity.y)
		velocity.y = Maxvelocity.y;

	set_position(get_position() + velocity);
}

void VelocityAgent::draw(aie::Renderer2D* renderer)
{
	renderer->drawCircle(m_Position.x, m_Position.y, dotSize);
}

void VelocityAgent::add_force(Vector2 force)
{
	velocity += force;
}
