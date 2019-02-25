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
		vel += behav->update(this, deltatime);
	}
	
	if (vel.x > max_velocity)
	{
		vel.x = max_velocity;
	}
	if (vel.y > max_velocity)
	{
		vel.y = max_velocity;
	}
	if (vel.x < -max_velocity)
	{
		vel.x = -max_velocity;
	}
	if (vel.y < -max_velocity)
	{
		vel.y = -max_velocity;
	}
	vel *= 0.9f;
	auto mod = (rand() % (5 - 15) + 1);
	auto a = vel * speed * mod * deltatime;
	pos += a;

	return SUCCESS;
}
