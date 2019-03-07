#include "ArrivingBehaviour.h"
#include "Object.h"


ArrivingBehaviour::ArrivingBehaviour()
{
}


ArrivingBehaviour::~ArrivingBehaviour()
{
}

Vector2 ArrivingBehaviour::update(Object* agent, float deltaTime)
{
	Vector2 desired = m_target->pos - agent->pos;


	float d = desired.magnitude();
	desired.normalise();

	if (d < 100) {

		//scaled position = new rangebegining + (new rangeending - new rangebegining) * ((positionbescaled - old rangebegining) / (old rangeending - old rangebegining))
		float scaled = 0 + (agent->max_velocity - 0) * ((d - 0) / (100 - 0));

		desired *= scaled;
	}
	else {

		desired *= agent->max_velocity;
	}


	Vector2 steer = desired - agent->vel;
	steer.limit(agent->max_force);
	agent->apply_force(steer);

	return Vector2();
}
