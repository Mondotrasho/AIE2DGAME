#pragma once
#include "Behaviour.h"
#include "NavMesh.h"
#include "GameObject.h"

class CheckInRangeOfFood : public Behaviour
{
public:
	CheckInRangeOfFood()
	{
	}

	CheckInRangeOfFood(NavMesh* nav ,float newrange) : m_navMesh(nav) ,range(newrange){}

	~CheckInRangeOfFood()
	{
	}


	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		foodinrange.clear();

		for (auto object : *gameObject->ObjectPool)
		{
			if (object->isfood() && object->team == gameObject->team && object->position.distance(gameObject->position) < range)
			{
				foodinrange.push_back(object);
			}
		}
		if (!foodinrange.empty()) {
			GameObject* closestfood = foodinrange[0];
			for (auto food : foodinrange)
			{
				if (food->position.distance(gameObject->position) < closestfood->position.distance(gameObject->position))
					closestfood = food;
			}
			gameObject->set_target(closestfood);
			return SUCCESS;
		}
		return FAILURE;		
	}

	NavMesh* m_navMesh;
	float range;
	std::vector<GameObject*> foodinrange;
};
