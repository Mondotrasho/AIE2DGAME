#pragma once
#include "Edge.h"
#include "Vector2.h"
#include <string>
#include <vector>
#include "Renderer2D.h"

class Node
{
public:
	std::string Name;
	Vector2 Pos{ 0,0 };
	float G{ std::numeric_limits<float>::infinity() };
	float H;
	float F;	
	Node* N{ nullptr };
	std::vector<Edge*> Connections;
	std::vector<Vector2> vertices;
	// finds any vertices that are shared with the other node
	int getAdjacentVertices(Node* other, Vector2* adjacent) {
		int count = 0;
		for (auto v : vertices) {
			for (auto v2 : other->vertices) {
				if (v.x == v2.x &&
					v.y == v2.y) {
					adjacent[count++] = v;
					break;
				}
			}
		}
		return count;
	}
	static float heuristic(Node* a, Node* b) {
		Node* s = (Node*)a;
		Node* e = (Node*)b;
		float x = e->Pos.x - s->Pos.x;
		float y = e->Pos.y - s->Pos.y;
		return x * x + y * y;
	}
	Node() {}
	Node(std::string label, Vector2 pos) : Name(label), Pos(pos) {}
	virtual ~Node()
	{
		//todo DO
		for (auto e : Connections) delete e;
		
	}

	void Draw(aie::Renderer2D* m_2dRenderer)
	{
		m_2dRenderer->setRenderColour(1, 1, 0);
		m_2dRenderer->drawCircle(Pos.x, Pos.y, 1);

				for (auto con : Connections)
		{
			m_2dRenderer->setRenderColour(0, 1, 0);
			//m_2dRenderer->drawLine(Pos.x, Pos.y, con->m_target->Pos.x, con->m_target->Pos.y, con->Cost);
		}
	}
};
