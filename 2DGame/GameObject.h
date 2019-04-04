#pragma once
#include "Vector2.h"
#include <list>
#include "Node.h"
#include "Behaviour.h"
#include <algorithm>
#include "Sprite.h"

enum eTeam {
	Blue,
	Red,
	None
};


class GameObject
{
	public:	
	GameObject();
	GameObject(Vector2 Pos, float Speed, std::vector<GameObject*>* newpool,Node* mynode = nullptr, eTeam myteam = None) : position(Pos), speed(Speed), ObjectPool(newpool) ,  team(myteam)
	{
	}

	~GameObject();

	Vector2 position = {};
	float speed = 50;
	float size= 5;
	eTeam team;
	Node* Occupied{};
	GameObject* target = nullptr;
	std::vector<GameObject*>* ObjectPool;
	Sprite sprite;
	bool deleteme = false;
	float angle = 0;

	void set_target(GameObject* newtarget)
	{
		target = newtarget;
	}
	void set_pool(std::vector<GameObject*>* newpool)
	{
		ObjectPool = newpool;
	}
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


	virtual void Draw(aie::Renderer2D* render)
	{
		render->drawCircle(position.x, position.y, size);
	}

	// these are used by the NavMesh behaviours
	std::list<Vector2> smoothPath;
	std::list<Node*> path;

	std::vector<Behaviour*> behaviours;

	//checking type
	virtual bool isfood() { return false; }
	virtual bool isfish() { return false; }
	virtual bool isschool() { return false; }

	//moves off screen clears values and removes itself from the object pool
	void remove()
	{
		deleteme = true;
		position = {9999,9999};
		speed = 0;
		size = 1;
		team = None;
		Occupied= nullptr;
		target = nullptr;
		sprite.setScale(1, 1);
	}

	void addtopool()
	{
		ObjectPool->emplace_back(this);
	}
};

inline GameObject::GameObject()//: ObjectPool(new std::vector<GameObject*>() )
{
}

inline GameObject::~GameObject()
{
}
