#ifndef FOLLOWBEHAVIOUR_H
#define FOLLOWBEHAVIOUR_H

#include "Behaviour.h"



class FollowBehaviour : public Behaviour {
public:
	FollowBehaviour();
	virtual ~FollowBehaviour();
	eBehaviourResult update(GameObject* gameObject, float deltaTime) override;
	void setSpeed(float speed) { m_speed = speed; }
	void setTarget(GameObject* gameObject) { m_target = gameObject; }
private:
	float m_speed;
	GameObject* m_target;
};


#endif // FOLLOWBEHAVIOUR_H
