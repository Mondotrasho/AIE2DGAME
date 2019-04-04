#pragma once
#include "Behaviour.h"
#include "NavMesh.h"
#include "GameObject.h"

class CheckInRangeOfEdibleFish : public Behaviour
{
public:
	CheckInRangeOfEdibleFish()
	{
	}

	CheckInRangeOfEdibleFish(NavMesh* nav, float newrange) : m_navMesh(nav), range(newrange) {}

	~CheckInRangeOfEdibleFish()
	{
	}


	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		ediblefishinrange.clear();

		for (auto object : *gameObject->ObjectPool)
		{
			if (object != gameObject && object->isfish() && object->team != gameObject->team && object->position.distance(gameObject->position) < range)
			{
				if(object->size < gameObject->size && object->size > gameObject->size * 0.5f)
				ediblefishinrange.push_back(object);
			}
		}
		if (!ediblefishinrange.empty()) {
			GameObject* closestfood = ediblefishinrange[0];
			for (auto food : ediblefishinrange)
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
	std::vector<GameObject*> ediblefishinrange;
};
