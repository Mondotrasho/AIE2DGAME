#include "SeperationBehaviour.h"
#include <vector>
#include "Object.h"


SeperationBehaviour::~SeperationBehaviour()
{
}

Vector2 SeperationBehaviour::update(Object * agent, float deltaTime)
{
	Vector2 separateForce = Vector2(0, 0);
	//std::vector<Object*> neighbourhood;
	//for each (auto obj in objectpool)
	//{
	//	if (obj->get_position().distance(agent->get_position()) < neighbourhoodrad)
	//	{
	//		neighbourhood.push_back(obj);
	//	}
	//}

	for each (auto b in agent->neighbourhood)
	{
		separateForce += agent->get_position() - b->get_position();
		// average separation force

	}
	separateForce /= agent->neighbourhood.size();
	Vector2 steer = ((separateForce - agent->get_velocity())* separateWeight);
	//steer.limit(agent->max_force);
	agent->apply_force(steer);
	return Vector2(0,0);
}

