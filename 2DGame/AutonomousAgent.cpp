#include "AutonomousAgent.h"


AutonomousAgent::AutonomousAgent(): Object()
{

}

Vector2 AutonomousAgent::GetMaxforce()
{
	return Vector2(0, 0);
}

AutonomousAgent::~AutonomousAgent()
{
}

eBehaviourResult AutonomousAgent::update(float deltatime)
{
	for each(Behaviour* behav in behaviours)
	{
		vel = behav->update(this, deltatime);
	}

	pos += vel * max_velocity  * deltatime;

	return SUCCESS;
}
