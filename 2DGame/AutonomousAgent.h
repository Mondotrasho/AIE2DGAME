#pragma once
#include "Object.h"
#include "Behaviour.h"
#include <vector>

class AutonomousAgent : public Object
{
public:
	AutonomousAgent();
	~AutonomousAgent();
	AutonomousAgent(Vector2 Pos, Vector2 Vel, float Size,float MaxV = 10) : Object(Pos, Vel, Size, MaxV){}
	eBehaviourResult update(float deltatime);
	Vector2 GetMaxforce();

	std::vector<Behaviour*> behaviours;

	void addbehaviour(Behaviour* behave)
	{
		behaviours.push_back(behave);
	}
};

