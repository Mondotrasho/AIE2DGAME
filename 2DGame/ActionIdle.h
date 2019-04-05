#pragma once
#include "Behaviour.h"
#include "Vector2.h"
#include "NavMesh.h"
#include "Astar.h"
#include "GameObject.h"

//generates a idle path
class ActionIdle :
	public Behaviour
{
public:
	ActionIdle(){};
	ActionIdle(NavMesh* nav) : m_navMesh(nav){}
	~ActionIdle(){};
	eBehaviourResult execute(GameObject* gameObject, float deltaTime) override;

	NavMesh* m_navMesh;

};

inline eBehaviourResult ActionIdle::execute(GameObject* gameObject, float deltaTime)
{
	if (gameObject->smoothPath.empty()) {
		// random end node
		bool found = false;
		do {
			//reset nodesscores
			for (auto node : m_navMesh->getNodes())
			{
				node->G = std::numeric_limits<float>::infinity();
				node->H = 0;
				node->F = 0;
				node->N = nullptr;
			}
			if (gameObject->Occupied == nullptr) { return FAILURE; }
			auto first = gameObject->Occupied;//m_navMesh->findClosest(gameObject->position.x, gameObject->position.y);
			auto end = m_navMesh->getRandomNode();

			AStar astar;

			found = astar.AStarSearch(first, end, gameObject->path, Node::heuristic(first, end));

		} while (found == false);

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
	}return FAILURE;
}