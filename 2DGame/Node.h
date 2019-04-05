#pragma once
#include "Edge.h"
#include "Vector2.h"
#include <string>
#include <vector>
#include "Renderer2D.h"

class Node
{
public:
	Node() = default;
	Node(std::string label, Vector2 pos) : Name(label), Pos(pos) {}
	virtual ~Node();

	std::string Name;
	Vector2 Pos{ 0,0 };
	float G{ std::numeric_limits<float>::infinity() };//cost to get there
	float H{};//heuristic from that point
	float F{};
	Node* N{ nullptr };	//parent node
	std::vector<Edge*> Connections;
	std::vector<Vector2> vertices;

	// finds any vertices that are shared with the other node
	int getAdjacentVertices(Node* other, Vector2* adjacent);
	//don't use this anymore still keeping for when I do
	static float heuristic(Node* a, Node* b);

	void Draw(aie::Renderer2D* m_2dRenderer);
};

inline int Node::getAdjacentVertices(Node* other, Vector2* adjacent)
{
	int count = 0;
	for (auto v : vertices)
	{
		for (auto v2 : other->vertices)
		{
			if (v.x == v2.x &&
				v.y == v2.y)
			{
				adjacent[count++] = v;
				break;
			}
		}
	}
	return count;
}

inline float Node::heuristic(Node* a, Node* b)
{
	Node* s = (Node*)a;
	Node* e = (Node*)b;
	float x = e->Pos.x - s->Pos.x;
	float y = e->Pos.y - s->Pos.y;
	return x * x + y * y;
}

inline Node::~Node()
{
	//todo DO
	for (auto e : Connections)
		delete e;
}

inline void Node::Draw(aie::Renderer2D* m_2dRenderer)
{
	m_2dRenderer->setRenderColour(1, 1, 0);
	m_2dRenderer->drawCircle(Pos.x, Pos.y, 1);

	for (auto con : Connections)
	{
		m_2dRenderer->setRenderColour(0, 1, 0);
		//m_2dRenderer->drawLine(Pos.x, Pos.y, con->m_target->Pos.x, con->m_target->Pos.y, con->Cost);
	}
}
