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
	float F;	Node* N{ nullptr };
	std::vector<Edge> Connections;

	Node(std::string label, Vector2 pos) : Name(label), Pos(pos) {}
	~Node() = default;

	void Draw(aie::Renderer2D* m_2dRenderer)
	{
		m_2dRenderer->setRenderColour(1, 1, 0);
		m_2dRenderer->drawCircle(Pos.x, Pos.y, 10);
		for (auto con : Connections)
		{
			m_2dRenderer->setRenderColour(0, 1, 0);
			m_2dRenderer->drawLine(Pos.x, Pos.y, con.m_target->Pos.x, con.m_target->Pos.y, con.Cost);
		}
	}
};
