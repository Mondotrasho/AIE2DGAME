#ifndef FOLLOWBEHAVIOUR_H
#define FOLLOWBEHAVIOUR_H

#include "Behaviour.h"
class FollowBehaviour : public Behaviour {
public:

	FollowBehaviour();
	virtual ~FollowBehaviour();

	eBehaviourResult update(Agent* agent, float deltaTime) override;

	void setSpeed(float speed) { m_speed = speed; }
	void setTarget(Agent* gameObject) { m_target = gameObject; }

private:

	float m_speed;
	Agent* m_target;
};


#endif // FOLLOWBEHAVIOUR_H
