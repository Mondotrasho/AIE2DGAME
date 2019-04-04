#pragma once
#include "Behaviour.h"
#include "GameObject.h"
#include "NavMesh.h"
#include "Astar.h"

//make sure target has ActionFindMyNode attached
class ActionPathAwayFromTarget : public Behaviour
{
public:
	ActionPathAwayFromTarget()
	{
	}

	ActionPathAwayFromTarget(NavMesh* nav) :m_navMesh(nav) {}

	~ActionPathAwayFromTarget()
	{
	}


	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override
	{
		if (gameObject->target != nullptr) {
			if (gameObject->target->isfish()) {
				if (!gameObject->smoothPath.empty()) {
					if(gameObject->smoothPath.front().distance(gameObject->hunter->position) <= gameObject->position.distance(gameObject->hunter->position))
					{
						return SUCCESS;
					}					
				}
			}
		}
		//if (!gameObject->path.empty() && gameObject->target != nullptr) { return SUCCESS; }
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
		auto escapepoint = gameObject->position - gameObject->target->position;
		auto end = m_navMesh->findClosest(escapepoint.x,escapepoint.y);

		if (end == gameObject->path.back())
		{
			return SUCCESS;
		}

		AStar astar;

		bool found = astar.AStarSearch(first, end, gameObject->path, Node::heuristic(first, end));


		//smooth if large enough
		if (gameObject->path.size() > 1)
			NavMesh::smoothPath(gameObject->path, gameObject->smoothPath);
		else
		{
			for (auto node : gameObject->path)
			{
				gameObject->smoothPath = { node->Pos };
			}
		}

		return SUCCESS;
		//}
		//	return FAILURE;

	}

	NavMesh* m_navMesh;

};
