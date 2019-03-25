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
	//for each(Behaviour* behav in behaviours)
	//{
	//	acc += behav->update(this, deltatime);
	//}
	//
	//	if (vel.x > max_velocity)
	//	{
	//		vel.x = max_velocity;
	//	}
	//	if (vel.y > max_velocity)
	//	{
	//		vel.y = max_velocity;
	//	}
	//	if (vel.x < -max_velocity)
	//	{
	//		vel.x = -max_velocity;
	//	}
	//	if (vel.y < -max_velocity)
	//	{
	//		vel.y = -max_velocity;
	//	}
	//
	//auto mod = (rand() % (5 - 15) + 1);
	//auto a = vel * mod * deltatime;
	//vel += acc.normalised();
	//vel *= 0.99f;
	//pos += vel;
	//acc = Vector2(0, 0);
	//
	//

	
	float Neighbourrad = 19;
	for each (auto obj in objectpool)
	{
		if (obj->get_position().distance(this->get_position()) < Neighbourrad)
		{
			neighbourhood.push_back(obj);
		}
	}

	for each(Behaviour* behav in behaviours)
	{
		behav->update(this, deltatime);
	}
	//force.limit(max_force);
	acc += force * deltatime;
	vel += acc;
	//vel.limit(max_velocity);
	pos += vel;
	acc *= 0;

	return SUCCESS;
}
