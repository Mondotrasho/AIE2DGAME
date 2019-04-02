#pragma once
#include "Behaviour.h"
#include "Vector2.h"
#include <list>
#include "NavMesh.h"

class MouseGenPathBehaviour :
	public Behaviour
{
public:
	MouseGenPathBehaviour() = default;
	MouseGenPathBehaviour(NavMesh* navMesh, std::list<Vector2>& smoothPath):m_navMesh(navMesh), m_smoothPath(smoothPath){}
	virtual ~MouseGenPathBehaviour();

	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime);

	NavMesh* m_navMesh;
	std::list<Vector2>& m_smoothPath;

	void settarget(GameObject* target)
	{
		mouse = target;
	}

	GameObject* mouse = nullptr;
};

