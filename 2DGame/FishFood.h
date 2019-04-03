#pragma once
#include "GameObject.h"
class FishFood :
	public GameObject
{
public:
	FishFood() = default;
	FishFood(const Vector2& Pos, int Speed, std::vector<GameObject*>* newpool, Node* mynode = nullptr, eTeam myteam = None) : GameObject(Pos, Speed,newpool, mynode, myteam) {}

	~FishFood() = default;

	virtual bool isfood() { return true; }
	virtual bool isfish() { return false; }
	virtual bool isschool() { return false; }
};

