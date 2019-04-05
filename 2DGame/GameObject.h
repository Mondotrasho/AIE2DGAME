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
	GameObject(Vector2 Pos, float Speed, std::vector<GameObject*>* newpool,Node* mynode = nullptr, eTeam myteam = None) : position(Pos), speed(Speed), ObjectPool(newpool) ,  team(myteam){}
	~GameObject();

	//variables
	float speed = 50;
	float size= 5;
	float angle = 0;
	eTeam team;
	Sprite sprite;
	Node* Occupied{};
	bool deleteme = false;
	Vector2 position = {};
	std::list<Node*> path;
	GameObject* target = nullptr;
	GameObject* hunter = nullptr;
	std::list<Vector2> smoothPath;
	std::vector<GameObject*>* ObjectPool;
	std::vector<Behaviour*> behaviours;

	//setters
	void set_target(GameObject* newtarget);
	void set_pool(std::vector<GameObject*>* newpool);
	void set_position(Vector2 newpos);
	void set_speed(float newspeed);
	void set_size(float newsize);
	void addbehaviour(Behaviour* behave);

	//getters
	Vector2 get_position();
	float get_speed();
	float get_size();

	//gameloop
	void Update(float delta);
	virtual void Draw(aie::Renderer2D* render);
	
	//checking type
	virtual bool isfood() { return false; }
	virtual bool isfish() { return false; }
	virtual bool isschool() { return false; }

	//managing objectpool
	//moves off screen clears values and tags itself for cleanup
	void remove();
	void addtopool();
};

inline GameObject::GameObject()//: ObjectPool(new std::vector<GameObject*>() )
{
}

inline GameObject::~GameObject()
{
}

inline void GameObject::set_target(GameObject* newtarget)
{
	target = newtarget;
}

inline void GameObject::set_pool(std::vector<GameObject*>* newpool)
{
	ObjectPool = newpool;
}

inline void GameObject::set_position(Vector2 newpos)
{
	position = newpos;
}

inline Vector2 GameObject::get_position()
{
	return position;
}

inline void GameObject::set_speed(float newspeed)
{
	speed = newspeed;
}

inline float GameObject::get_speed()
{
	return speed;
}

inline void GameObject::set_size(float newsize)
{
	size = newsize;
}

inline float GameObject::get_size()
{
	return size;
}

inline void GameObject::addbehaviour(Behaviour* behave)
{
	behaviours.push_back(behave);
}

inline void GameObject::Update(float delta)
{
	for (auto b : behaviours)
	{
		b->execute(this, delta);
	}
}

inline void GameObject::Draw(aie::Renderer2D* render)
{
	render->drawCircle(position.x, position.y, size);
}

inline void GameObject::remove()
{
	deleteme = true;
	position = {9999, 9999};
	speed = 0;
	size = 1;
	team = None;
	Occupied = nullptr;
	target = nullptr;
	sprite.setScale(1, 1);
}

inline void GameObject::addtopool()
{
	ObjectPool->emplace_back(this);
}
