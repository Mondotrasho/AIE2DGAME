#include "PlayerControlledState.h"
#include "Input.h"
#include "Vector2.h"
#include "GameDefs.h"
#include "GameObject.h"


PlayerControlledState::PlayerControlledState()
{
}


PlayerControlledState::~PlayerControlledState()
{
}

void PlayerControlledState::onUpdate(GameObject* object, float deltaTime) {

	aie::Input* input = aie::Input::getInstance();

	float rot = object->getRotation();
	float speed = object->getSpeed();
	Vector2 pos = object->getPosition();
	if (input->isKeyDown(aie::INPUT_KEY_UP)) {
		Vector2 vel = { cos(rot) * speed * deltaTime, sin(rot) * speed * deltaTime };
		object->setPosition({ pos.x + vel.x, pos.y + vel.y });
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT)) {
		rot += RADIANS * speed * deltaTime;
		object->setRotation(rot);
	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT)) {
		rot -= RADIANS * speed * deltaTime;
		object->setRotation(rot);
	}
}