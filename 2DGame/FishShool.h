#pragma once
#include "GameObject.h"
class FishShool :
	public GameObject
{
public:
	FishShool();
	FishShool(const Vector2& vector2, int i)
	{
		position = vector2;
		speed = i;
	};
	~FishShool();

	GameObject fish[8];
};

