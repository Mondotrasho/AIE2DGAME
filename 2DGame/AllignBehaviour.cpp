#include "AllignBehaviour.h"
#include "Object.h"


AllignBehaviour::~AllignBehaviour()
{
}


Vector2 AllignBehaviour::update(Object * agent, float deltaTime)
{
	Vector2 Allignforce = Vector2(0, 0);
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
		Allignforce += b->get_velocity();
		// average separation force
	}
	Allignforce /= agent->neighbourhood.size();
	Vector2 steer = ((Allignforce - agent->get_velocity()) * AllignWeight);
	//steer.limit(agent->max_force);
	agent->apply_force(steer);
	return Vector2(0, 0);

}