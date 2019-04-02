#pragma once
#include "Behaviour.h"
#include "NavMesh.h"

class FindMyNode : public Behaviour
{
public:
	FindMyNode();
	FindMyNode(NavMesh* nav):m_navMesh(nav){}
	~FindMyNode();
	
	
	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override;

	NavMesh* m_navMesh;
};

