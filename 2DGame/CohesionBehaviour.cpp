#include "CohesionBehaviour.h"
#include "Object.h"


CohesionBehaviour::~CohesionBehaviour()
{
}

Vector2 CohesionBehaviour::update(Object * agent, float deltaTime)
{
	Vector2 Cohesionforce = Vector2(0, 0);
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
		Cohesionforce += b->get_position() - agent->get_position();
	}
	Cohesionforce /= agent->neighbourhood.size();
	Vector2 steer =((Cohesionforce - agent->get_velocity()) * CohesionWeight);
	//steer.limit(agent->max_force);
	agent->apply_force(steer);
	return Vector2(0, 0);
}