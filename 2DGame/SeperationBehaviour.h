#pragma once
#include "Behaviour.h"
#include <vector>

class SeperationBehaviour : public Behaviour {

public:


	SeperationBehaviour(float weight,float neighbourhhoodradius , std::vector<Object*> pool):separateWeight(weight),neighbourhoodrad(neighbourhhoodradius),objectpool(pool){}
	virtual ~SeperationBehaviour();

	Vector2 update(Object* agent, float deltaTime) override;

private:
	float separateWeight;
	float neighbourhoodrad;
	std::vector<Object*> objectpool;
};
	


