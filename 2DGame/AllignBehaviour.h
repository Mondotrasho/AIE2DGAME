#pragma once
#include "Behaviour.h"
#include <vector>

class AllignBehaviour :	public Behaviour
{
public:
	AllignBehaviour(float weight, float neighbourhhoodradius, std::vector<Object*> pool) :AllignWeight(weight), neighbourhoodrad(neighbourhhoodradius), objectpool(pool) {}
	~AllignBehaviour();
	Vector2 update(Object* agent, float deltaTime);

private:
	float AllignWeight;
	float neighbourhoodrad;
	std::vector<Object*> objectpool;
};

