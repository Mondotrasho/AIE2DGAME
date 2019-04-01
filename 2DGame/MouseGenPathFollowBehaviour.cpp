#include "MouseGenPathFollowBehaviour.h"
#include "NavMesh.h"
#include "GameObject.h"
#include "Astar.h"


MouseGenPathBehaviour::~MouseGenPathBehaviour()
{
}

bool MouseGenPathBehaviour::execute(GameObject* gameObject, float deltaTime)
{// random end node
	bool found = false;
	auto first = m_navMesh->findClosest(gameObject->position.x, gameObject->position.y);
	auto end = m_navMesh->findClosest(mouse->position.x, mouse->position.y);
	if (gameObject->smoothPath.empty() && first != end) {
		do {
			for (auto node : m_navMesh->getNodes())
			{
				node->G = std::numeric_limits<float>::infinity();
				node->H = 0;
				node->F = 0;
				node->N = nullptr;
			}
			//auto first = m_navMesh->findClosest(gameObject->position.x, gameObject->position.y);
			//auto end = m_navMesh->findClosest(mouse->position.x, mouse->position.y);

#pragma message("TODO: USe your own A* method here!")
			AStar astar;
			

			found = astar.AStarSearch(first, end, gameObject->path, Node::heuristic(first, end));

		} while (found == false);
		if (gameObject->path.size() > 1)
			NavMesh::smoothPath(gameObject->path, m_smoothPath);
	}
	return true;
}
