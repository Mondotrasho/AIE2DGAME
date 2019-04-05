#pragma once
#include "Behaviour.h"
#include "NavMesh.h"

class ActionFindMyNode : public Behaviour
{
public:
	ActionFindMyNode(){};
	ActionFindMyNode(NavMesh* nav):m_navMesh(nav){}
	~ActionFindMyNode(){};	
	
	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override;

	NavMesh* m_navMesh;
};

inline eBehaviourResult ActionFindMyNode::execute(GameObject* gameObject, float deltaTime)
{
	gameObject->Occupied = m_navMesh->findClosest(gameObject->position.x, gameObject->position.y);
	return SUCCESS;
}

