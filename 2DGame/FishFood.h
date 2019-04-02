#pragma once
#include "GameObject.h"
class FishFood :
	public GameObject
{
public:
	FishFood() = default;
	FishFood(const Vector2& Pos, int Speed,Node* mynode = nullptr, eTeam myteam = None) : GameObject(Pos, Speed, mynode, myteam) {}

	~FishFood() = default;
};

