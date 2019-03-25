#pragma once
#include "Behaviour.h"
class UpdateNieghbourhood :
	public Behaviour
{
public:
	UpdateNieghbourhood();
	~UpdateNieghbourhood();
	Vector2 update(Object* agent, float deltaTime) override;
};

