#pragma once
#include "Behaviour.h"
#include "Vector2.h"
#include "NavMesh.h"

//generates a idle path
class ActionIdle :
	public Behaviour
{
public:
	ActionIdle();
	ActionIdle(NavMesh* nav) : m_navMesh(nav){}
	~ActionIdle();
	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override;

	NavMesh* m_navMesh;

};

