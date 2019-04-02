#pragma once
#include "Behaviour.h"
#include <vector>
#include "Node.h"
#include <list>
#include "GameObject.h"

class FishSchool :	public GameObject
{
public:
	FishSchool();
	FishSchool(Vector2 Pos, float Speed)
	{
		position = Pos;
		speed = Speed;
	};
	~FishSchool();


	std::list<Vector2> smoothPath;
	std::list<Node*> path;

	std::vector<Behaviour*> behaviours;

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
};

