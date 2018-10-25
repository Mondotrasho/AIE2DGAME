#ifndef KEYBOARDBEHAVIOUR_H
#define KEYBOARDBEHAVIOUR_H


#include "Input.h"
#include "IBehaviour.h"
#include "Agent.h"


class KeyboardBehaviour : public IBehaviour {
public:
	KeyboardBehaviour() = default;
	virtual ~KeyboardBehaviour() = default;
	eBehaviourResult update(GameObject* agent, float deltaTime) override;
	void setSpeed(float speed) { Speed = speed; }

	float Speed;
};


inline eBehaviourResult KeyboardBehaviour::update(GameObject* agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	Vector2 velocity = {0,0};

	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W) ) {
		//agent->AddForce(50);
		velocity.y += 1;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		//agent->AddForce(50);
		velocity.y -= 1;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		//agent->AddForce(50);
		velocity.x += 1;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		//agent->AddForce(50);
		velocity.x -= 1;
	}
	float x, y;
	agent->getPosition(&x, &y);

	agent->setPosition(x + velocity.x * Speed * deltaTime,y + velocity.y * Speed * deltaTime);
	return eBehaviourResult::SUCCESS;
}


#endif // KEYBOARDBEHAVIOUR_H
