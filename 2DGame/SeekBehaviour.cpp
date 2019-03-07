#include "SeekBehaviour.h"
#include "Object.h"


SeekBehaviour::SeekBehaviour()
{
}


SeekBehaviour::~SeekBehaviour()
{
}

Vector2 SeekBehaviour::update(Object* agent, float deltaTime)
{
	
	Vector2 desired = m_target->pos - agent->pos;
	desired.normalise();

	desired *= agent->max_velocity;

	Vector2 steer = desired - agent->vel;

	steer.limit(agent->max_force);

	agent->apply_force(steer);
	return Vector2();
}
