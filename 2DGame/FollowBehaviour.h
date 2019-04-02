#pragma once
#include "Behaviour.h"
class GameObject;

class FollowPathBehaviour : public Behaviour {
public:

	FollowPathBehaviour() {}
	virtual ~FollowPathBehaviour() {}

	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);
};
