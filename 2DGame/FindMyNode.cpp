#include "FindMyNode.h"
#include "GameObject.h"


FindMyNode::FindMyNode()
{
}


FindMyNode::~FindMyNode()
{
}

eBehaviourResult FindMyNode::execute(GameObject* gameObject, float deltaTime)
{
	gameObject->Occupied = m_navMesh->findClosest(gameObject->position.x, gameObject->position.y);
	return SUCCESS;
}
