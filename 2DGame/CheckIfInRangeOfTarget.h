#pragma once
#include "Behaviour.h"
#include "NavMesh.h"
#include "GameObject.h"

//CheckIfInRangeOfTarget


class CheckIfInRangeOfTarget : public Behaviour
{
public:
	CheckIfInRangeOfTarget(){}
	CheckIfInRangeOfTarget(float newrange) : range(newrange) {}
	~CheckIfInRangeOfTarget(){}

	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override;

	float range;
};

inline eBehaviourResult CheckIfInRangeOfTarget::execute(GameObject* gameObject, float deltaTime)
{
	if (gameObject->target->position.distance(gameObject->position) < range)
	{
		return SUCCESS;
	}
	return FAILURE;
}
