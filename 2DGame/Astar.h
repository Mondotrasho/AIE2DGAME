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
	bool AStarSearch(Node* startNode, Node* endNode, std::list<Node*>& path,float Heuristic)
	{
		//Let openList be a List of Nodes
		//	Let closedList be a List of Nodes
		//	Set startNode.parent to null
		//	Add startNode to openList
		//	While openList is not empty
		//	Sort openList by Node.gScore


		auto cmp = [](Node* left, Node* right) { return left->F < right->F; };
		std::list<Node*> openList;
		std::list<Node*> closedList;

		startNode->G = 0;
		startNode->N = nullptr;

		if (startNode == endNode)
		{
			return false;
		}
		std::list<Node*>::iterator it = openList.begin();
		openList.insert(it,startNode);

		while (!openList.empty())
		{
			//sort by F
			//std::sort(openList.begin(), openList.end(), cmp);
			openList.sort(cmp);

			Node* currentNode = openList.front();
			if (currentNode == endNode) { break; }

			openList.remove(currentNode); //with seed of 1 it causes heap curruption on hit 69

			std::list<Node*>::iterator it = closedList.begin();
			closedList.insert(it, currentNode);	

			for (Edge* edge : currentNode->Connections)
			{
				//if its not in the
				if(!(std::find(closedList.begin(), closedList.end(), edge->m_target) != closedList.end()))
				{
					auto gScore = currentNode->G + edge->Cost;
					 auto hScore = edge->m_target->Pos.distance(endNode->Pos);
					 auto fScore = gScore + hScore;

					// Have not yet visited the node.
					// So calculate the Score and update its parent.
					// Also add it to the openList for processing.
					 if (!(std::find(openList.begin(), openList.end(), edge->m_target) != openList.end()))
					 {
						 edge->m_target->G = gScore;
						 edge->m_target->F = fScore;
						 edge->m_target->N = currentNode;

						 std::list<Node*>::iterator it = openList.begin();
						 openList.insert(it, edge->m_target);
					 }
					 else {
						 // Node is already in the openList with a valid Score.
						 // So compare the calculated Score with the existing
						 // to find the shorter path.
						 if (fScore < edge->m_target->F) 
						 {
							 edge->m_target->G = gScore;
							 edge->m_target->F = fScore;
							 edge->m_target->N = currentNode;
						 }
					 }
				}
			}
		}
	
		Node* currentNode = endNode;
		std::list<Node*> newpath;

		while (currentNode != nullptr) {
			newpath.push_front(currentNode);
			currentNode = currentNode->N;

		}
		path = newpath;
		return true;

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