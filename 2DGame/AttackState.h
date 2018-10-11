#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H
#include "State.h"
#include "GameObject.h"
#include "Vector2.h"

class AttackState : public State {
public:
	AttackState(GameObject* target, float speed) : m_target(target), m_speed(speed) {}
	virtual ~AttackState() = default;
	virtual void update(GameObject* gameObject, float deltaTime);
private:
	float m_speed;
	GameObject* m_target;
};

inline void AttackState::update(GameObject* gameObject, float deltaTime)
{
	Vector2 you;
	m_target->getPosition(&you.x, &you.y);
	Vector2 me;
	gameObject->getPosition(&me.x, &me.y);
	float distance = abs(you.x - me.x) + abs(you.y - me.y) ;

	Vector2 dir = me - you;

	if(distance > 0)
	{
		dir = dir.normalised();

		auto newpos = me - dir * deltaTime * 50.0f;

		gameObject->setPosition(newpos.x, newpos.y);
	}
}
#endif // ATTACKSTATE_H
