#ifndef FOLLOWBEHAVIOUR_H
#define FOLLOWBEHAVIOUR_H

#include "Behaviour.h"
#include "AutonomousAgent.h"

class FollowBehaviour : public Behaviour {
public:

	FollowBehaviour(float Range = 1.0f):range(Range){}
	virtual ~FollowBehaviour();

	Vector2 update(Object* agent, float deltaTime) override;

	void setTarget(Object* gameObject) { m_target = gameObject; }

private:

	Object* m_target;
	float range;
};


#endif // FOLLOWBEHAVIOUR_H
