#pragma once
#include "Behaviour.h"
#include <vector>

class CohesionBehaviour :
	public Behaviour
{
public:
	CohesionBehaviour(float weight, float neighbourhhoodradius, std::vector<Object*> pool) :CohesionWeight(weight), neighbourhoodrad(neighbourhhoodradius), objectpool(pool) {}
	~CohesionBehaviour();
	Vector2 update(Object* agent, float deltaTime);

private:
	float CohesionWeight;
	float neighbourhoodrad;
	std::vector<Object*> objectpool;
};

