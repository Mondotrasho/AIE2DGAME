#ifndef FOLLOWBEHAVIOUR_H
#define FOLLOWBEHAVIOUR_H

#include "IBehaviour.h"


class Agent;

class FollowBehaviour : public IBehaviour {
public:
	FollowBehaviour();
	virtual ~FollowBehaviour();
	eBehaviourResult update(Agent* agent, float deltaTime);
	void setSpeed(float speed) { m_speed = speed; }
	void setTarget(Agent* agent) { m_target = agent; }
private:
	float m_speed;
	Agent* m_target;
};


#endif // FOLLOWBEHAVIOUR_H
