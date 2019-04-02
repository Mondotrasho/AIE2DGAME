#pragma once
#include "GameObject.h"
class FishShool :
	public GameObject
{
public:
	FishShool();
	FishShool(const Vector2& Pos, int Speed, Node* mynode = nullptr, eTeam myteam = None) : GameObject(Pos, Speed, mynode, myteam) {}

	~FishShool();

	GameObject fish[8];
};

