#pragma once
#include "Vector2.h"
#include <vector>
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
