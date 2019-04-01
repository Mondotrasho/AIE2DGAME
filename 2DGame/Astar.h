#pragma once
#include "Vector2.h"
#include <vector>
#include <set>
#include <queue>
#include <list>
#include "Node.h"
#include "Edge.h"

class AStar
{
public:
	std::list<Node*> AStarSearch(Node* startNode, Node* endNode)
	{
		//Let openList be a List of Nodes
		//	Let closedList be a List of Nodes
		//	Set startNode.parent to null
		//	Add startNode to openList
		//	While openList is not empty
		//	Sort openList by Node.gScore


		auto cmp = [](Node* left, Node* right) { return left->F > right->F; };
		std::priority_queue< Node*, std::vector<Node*>, decltype(cmp)> openList(cmp);

		std::set<Node*> closedList;

		startNode->G = 0;
		openList.push(startNode);

		while (!openList.empty())
		{
			Node* currentNode = openList.top();
			openList.pop();

			if (currentNode == endNode) { break; }

			closedList.insert(currentNode);

			for (Edge& edge : currentNode->Connections)
			{
				float dist = currentNode->G + edge.Cost;

				if (dist < edge.m_target->G)
				{
					edge.m_target->G = currentNode->G + edge.Cost;
					edge.m_target->N = currentNode;
					edge.m_target->H = edge.m_target->Pos.distance(endNode->Pos);
					edge.m_target->F = edge.m_target->G + edge.m_target->H;
				}

				if (closedList.find(edge.m_target) == closedList.end())
				{
					openList.push(edge.m_target);
				}
				////			Add c.target to openList if not in closedList
				//openList.push(edge.m_target);
				////			c.target.gScore = currentNode.gScore + c.cost
				//edge.m_target->G = currentNode->G + edge.Cost;
				////			c.target.parent = currentNode
				//edge.m_target->N = currentNode;
			}

		}
		Node* currentNode = endNode;
		std::list<Node*> path;

		while (currentNode != nullptr) {
			path.push_front(currentNode);
			currentNode = currentNode->N;

		}
		return path;

	}


	AStar();
	~AStar();
	void Draw(const std::list<Node*>& list, aie::Renderer2D* m_2dRenderer);
};

inline AStar::AStar()
{
}

inline AStar::~AStar()
{
}

inline void AStar::Draw(const std::list<Node*>& list, aie::Renderer2D* m_2dRenderer)
{
	std::list<Node*> StarPath = list;

	Node * first = StarPath.front();
	Node * second = StarPath.front();

	StarPath.pop_front();
	while (!StarPath.empty()) {
		first = second;
		second = StarPath.front();
		StarPath.pop_front();
		m_2dRenderer->setRenderColour(1, 0, 0);
		m_2dRenderer->drawLine(first->Pos.x, first->Pos.y, second->Pos.x, second->Pos.y, 10);

	}
}