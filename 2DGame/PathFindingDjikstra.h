#pragma once
#include "Vector2.h"
#include <vector>
#include <set>
#include <queue>
#include <list>
struct Edge;

struct Node
{
	std::string Name;
	Vector2 Pos{ 0,0 };
	float G{ std::numeric_limits<float>::infinity() };
	Node* N{ nullptr };
	std::vector<Edge> Connections;

	Node(std::string label, Vector2 pos) : Name(label), Pos(pos) {}
	~Node() = default;
};

struct Edge
{
	Node* m_target{ nullptr };
	float Cost{ 0 };

	Edge(Node* target, float cost) : m_target(target), Cost(cost) {}
	~Edge() = default;
};

class PathFindingDjikstra
{
public:
	std::list<Node*> dijkstrasSearch(Node* startNode, Node* endNode)
	{
		//Let openList be a List of Nodes
		//	Let closedList be a List of Nodes
		//	Set startNode.parent to null
		//	Add startNode to openList
		//	While openList is not empty
		//	Sort openList by Node.gScore


		auto cmp = [](Node* left, Node* right) { return left->G > right->G; };
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


	PathFindingDjikstra();
	~PathFindingDjikstra();
};

