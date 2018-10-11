#ifndef KEYBOARDBEHAVIOUR_H
#define KEYBOARDBEHAVIOUR_H


#include "Input.h"
#include "IBehaviour.h"
#include "Agent.h"


class KeyboardBehaviour : public IBehaviour {
public:
	KeyboardBehaviour() = default;
	virtual ~KeyboardBehaviour() = default;
	eBehaviourResult update(GameObject* gameObject, float deltaTime) override;
	eBehaviourResult update(Agent* agent, float deltaTime);
};

inline eBehaviourResult KeyboardBehaviour::update(GameObject* gameObject, float deltaTime)
{
}

inline eBehaviourResult KeyboardBehaviour::update(Agent* agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W) ) {
		agent->AddForce(50);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		agent->AddForce(50);
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		agent->AddForce(50);
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		agent->AddForce(50);
	}
}


#endif // KEYBOARDBEHAVIOUR_H
