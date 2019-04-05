#pragma once

#include "Behaviour.h"
#include "NavMesh.h"
#include "Astar.h"
#include "GameObject.h"

//make sure target has ActionFindMyNode attached
class ActionPathToMovingTarget : public Behaviour
{
public:
	ActionPathToMovingTarget(){}
	ActionPathToMovingTarget(NavMesh* nav) :m_navMesh(nav) {}
	~ActionPathToMovingTarget(){}

	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override;

	NavMesh* m_navMesh;

};

inline eBehaviourResult ActionPathToMovingTarget::execute(GameObject* gameObject, float deltaTime)
{
	if (gameObject->Occupied == gameObject->target->Occupied)
	{
		return SUCCESS;
	}
	if (gameObject->target != nullptr)
	{
		if (gameObject->target->isfish())
		{
			if (gameObject->target->Occupied == gameObject->path.back())
			{
				return SUCCESS;
			}
		}
	}

	//reset nodesscores
	for (auto node : m_navMesh->getNodes())
	{
		node->G = std::numeric_limits<float>::infinity();
		node->H = 0;
		node->F = 0;
		node->N = nullptr;
	}

	if (gameObject->target == nullptr || gameObject->target->Occupied == nullptr) { return FAILURE; }
	if (gameObject->Occupied == nullptr) { return FAILURE; }
	auto first = gameObject->Occupied;
	auto end = gameObject->target->Occupied;

	AStar astar;

	bool found = astar.AStarSearch(first, end, gameObject->path, Node::heuristic(first, end));


	//smooth if large enough
	if (gameObject->path.size() > 1)
		NavMesh::smoothPath(gameObject->path, gameObject->smoothPath);
	else
	{
		for (auto node : gameObject->path)
		{
			gameObject->smoothPath = {node->Pos};
		}
	}
	return SUCCESS;
}
