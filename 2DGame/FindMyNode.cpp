#include "ActionFindMyNode.h"
#include "GameObject.h"


ActionFindMyNode::ActionFindMyNode()
{
}


ActionFindMyNode::~ActionFindMyNode()
{
}

eBehaviourResult ActionFindMyNode::execute(GameObject* gameObject, float deltaTime)
{
	gameObject->Occupied = m_navMesh->findClosest(gameObject->position.x, gameObject->position.y);
	return SUCCESS;
}
