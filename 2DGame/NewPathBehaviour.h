#pragma once
#include "Vector2.h"
#include <list>
#include "NavMesh.h"
#include "Behaviour.h"

class GameObject;

// a behaviour that finds a new path and smooths it
class NewPathBehaviour : public Behaviour {
public:

	NewPathBehaviour(NavMesh* navMesh, std::list<Vector2>& smoothPath);
	virtual ~NewPathBehaviour() {}

	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

	NavMesh* m_navMesh;
	std::list<Vector2>& m_smoothPath;
};
