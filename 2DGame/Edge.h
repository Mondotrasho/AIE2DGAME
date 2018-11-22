#pragma once
#include "Node.h"

struct Edge
{
	Node* m_target{ nullptr };
	float Cost{ 0 };

	Edge(Node* target, float cost) : m_target(target), Cost(cost) {}
	~Edge() = default;
};
