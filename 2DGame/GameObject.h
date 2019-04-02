#pragma once
#include "Vector2.h"
#include <list>
#include "Node.h"
#include "Behaviour.h"

enum eTeam {
	Blue,
	Red,
	None
};


class GameObject
{
	public:	
	GameObject();
	GameObject(Vector2 Pos, float Speed,Node* mynode = nullptr, eTeam myteam = None) : position(Pos), speed(Speed) {}
	~GameObject();

	Vector2 position = {};
	float speed = 50;
	float size=6;
	eTeam team;
	Node* Occupied{};

	void set_position(Vector2 newpos)
	{
		position = newpos;
	}
	Vector2 get_position()
	{
		return position;
	}
	void set_speed(float newspeed)
	{
		speed = newspeed;
	}
	float get_speed()
	{
		return speed;
	}
	void set_size(float newsize)
	{
		size = newsize;
	}
	float get_size()
	{
		return size;
	}

	void addbehaviour(Behaviour* behave)
	{
		behaviours.push_back(behave);
	}

	void Update(float delta)
	{
		for (auto b : behaviours)
		{
			b->execute(this, delta);
		}
	}


	void Draw(aie::Renderer2D* render)
	{
		render->drawCircle(position.x, position.y, size);
	}

	// these are used by the NavMesh behaviours
	std::list<Vector2> smoothPath;
	std::list<Node*> path;

	std::vector<Behaviour*> behaviours;
};

inline GameObject::GameObject()
{
}

inline GameObject::~GameObject()
{
}
