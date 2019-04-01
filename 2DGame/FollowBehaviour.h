#pragma once
#include "Behaviour.h"
class GameObject;

class FollowPathBehaviour : public Behaviour {
public:

	FollowPathBehaviour() {}
	virtual ~FollowPathBehaviour() {}

	virtual bool execute(GameObject* gameObject, float deltaTime);
};
