#ifndef FOLLOWBEHAVIOUR_H
#define FOLLOWBEHAVIOUR_H

#include "IBehaviour.h"


class Agent;

class FollowBehaviour : public IBehaviour {
public:
	FollowBehaviour();
	virtual ~FollowBehaviour();
	eBehaviourResult update(GameObject* agent, float deltaTime) override;
	void setSpeed(float speed) { m_speed = speed; }
	void setTarget(GameObject* gameObject) { m_target = gameObject; }
private:
	float m_speed;
	GameObject* m_target;
};


#endif // FOLLOWBEHAVIOUR_H
