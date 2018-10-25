#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H
#include "State.h"
#include "GameObject.h"
#include "Vector2.h"

class AttackState : public State {
public:
	AttackState(Agent* target, float speed);
	virtual ~AttackState() = default;
	virtual void update(Agent* agent, float deltaTime);

private:
	float m_speed;
	Agent* m_target;
};

inline AttackState::AttackState(Agent* target, float speed): m_target(target), m_speed(speed)
{
	m_target = target;
	m_speed = speed;
}

inline void AttackState::update(Agent* agent, float deltaTime)
{
	Vector2 you = m_target->getPosition();
	Vector2 me = agent->getPosition();

	float distance = abs(you.x - me.x) + abs(you.y - me.y) ;

	Vector2 dir = me - you;

	if(distance > 0)
	{
		dir = dir.normalised();

		auto newpos = me - dir * deltaTime * m_speed;

		agent->setPosition(newpos);
	}
}
#endif // ATTACKSTATE_H
