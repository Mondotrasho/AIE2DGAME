#pragma once
#include "GameObject.h"
class FishShool :
	public GameObject
{
public:
	FishShool();
	FishShool(const Vector2& Pos, int Speed, std::vector<GameObject*>* newpool, Node* mynode = nullptr, eTeam myteam = None) : GameObject(Pos, Speed,newpool, mynode, myteam) {}

	~FishShool();

	GameObject fish[8];

	virtual bool isfood() { return false; }
	virtual bool isfish() { return true; }
	virtual bool isschool() { return false; }
};

