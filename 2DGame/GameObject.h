#pragma once
#include "Vector2.h"
#include <list>
#include "Node.h"
#include "Behaviour.h"

class GameObject
{
	public:
	Vector2 position = {};
	float speed = 50;

	void Update(float delta)
	{
		for (auto b : behaviours)
		{
			b->execute(this, delta);
		}
	}
	void Draw(aie::Renderer2D* render)
	{
		render->drawCircle(position.x, position.y, 3);
	}

	// these are used by the NavMesh behaviours
	std::list<Vector2> smoothPath;
	std::list<Node*> path;

	std::vector<Behaviour*> behaviours;
};
