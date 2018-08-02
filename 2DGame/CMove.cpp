#include "CMove.h"
#include "Input.h"

CMove::CMove()
= default;

Matrix3 CMove::getTransform()
{
	return	Transform;
}

void CMove::update(float deltaTime) 
{
	aie::Input* input = aie::Input::getInstance();
	
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		auto facing = getTransform()[1] * deltaTime * 100;
		translate(facing.x, facing.y);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		auto facing = getTransform()[1] * deltaTime * -100;
		translate(facing.x, facing.y);
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		rotate(-deltaTime);

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		rotate(deltaTime);
}

void CMove::setPosition(float x, float y) {
	Transform[2] = { x, y, 1 };
}
void CMove::setRotate(float radians) {
	Transform.set_rotate_z(radians);
}
void CMove::setScale(float width, float height) {
	Transform.set_scaled(width, height);
}
void CMove::translate(float x, float y) {
	Transform.translate(x, y);
}
void CMove::rotate(float radians) {
	Transform.rotate_z(radians);
}
void CMove::scale(float width, float height) {
	Transform.scale(width, height);
}