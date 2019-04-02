#pragma once
#include "Composite.h"
class Selector :
	public Composite
{
public:
	Selector();
	~Selector();
	eBehaviourResult execute(GameObject* agent, float deltaTime) override;
};

