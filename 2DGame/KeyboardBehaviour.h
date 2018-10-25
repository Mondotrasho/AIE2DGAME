#ifndef KEYBOARDBEHAVIOUR_H
#define KEYBOARDBEHAVIOUR_H


#include "Input.h"
#include "IBehaviour.h"
#include "Agent.h"


class KeyboardBehaviour : public IBehaviour {
public:
	KeyboardBehaviour() = default;
	virtual ~KeyboardBehaviour() = default;
	eBehaviourResult update(Agent* agent, float deltaTime) override;
	void setSpeed(float speed) { Speed = speed; }

	float Speed;
};


inline eBehaviourResult KeyboardBehaviour::update(Agent* agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W) ) {
		agent->AddForce(1);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		agent->AddForce(1);
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		agent->AddForce(1);
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		agent->AddForce(1);
	}
	return eBehaviourResult::SUCCESS;
}


#endif // KEYBOARDBEHAVIOUR_H
