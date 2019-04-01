#pragma once


class Node;

class Edge
{
public:

	Node* m_target{ nullptr };
	float Cost{ 0 };

	Edge() = default;
	Edge(Node* target, float cost) : m_target(target), Cost(cost) {}
	virtual ~Edge() = default;
};