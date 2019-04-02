#pragma once
#include "Behaviour.h"
#include <vector>

class Composite : public Behaviour
{
public:
	Composite();
	~Composite();


	eBehaviourResult execute(GameObject* agent, float deltaTime) override = 0;

	std::vector<Behaviour*> children;
};

