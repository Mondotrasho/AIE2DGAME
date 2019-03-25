#include "StayWithinBehaviour.h"
#include "Object.h"


StayWithinBehaviour::StayWithinBehaviour()
{
}


StayWithinBehaviour::~StayWithinBehaviour()
{
}

Vector2 StayWithinBehaviour::update(Object* agent, float deltaTime)
{
	if (agent->pos.x > x_axis_limits.Max) {

		Vector2 desired = Vector2(-agent->max_velocity, agent->vel.y);
		Vector2 steer = desired - agent->vel;

		//steer.limit(agent->max_force * mod);

		agent->apply_force(steer);
	}
	if (agent->pos.x < x_axis_limits.Min) {

		Vector2 desired = Vector2(agent->max_velocity, agent->vel.y);
		Vector2 steer = desired - agent->vel;

		//steer.limit(agent->max_force * mod);

		agent->apply_force(steer);
	}

	if (agent->pos.y > y_axis_limits.Max) {

		Vector2 desired = Vector2(agent->vel.x,-agent->max_velocity);
		Vector2 steer = desired - agent->vel;

		//steer.limit(agent->max_force * mod);

		agent->apply_force(steer);
	}
	if (agent->pos.y < y_axis_limits.Min) {

		Vector2 desired = Vector2(agent->vel.x, agent->max_velocity);
		Vector2 steer = desired - agent->vel;

		//steer.limit(agent->max_force * mod);

		agent->apply_force(steer);
	}
	return Vector2();
}
