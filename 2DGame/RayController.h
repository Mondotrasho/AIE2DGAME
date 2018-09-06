#pragma once
#include <cmath>
#include "Input.h"
#include "Ray.h"

inline void raycontroller(Ray& m_ray, float& m_rayAngle, Vector2& velocity, Plane ground, float deltaTime, bool grapstate)
{

	// input example
	aie::Input* input = aie::Input::getInstance();
	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W) && ground.distanceTo(m_ray.origin) < 20) {
		velocity.y += 50;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		//velocity.y -= 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		velocity.x += 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		velocity.x -= 4;
	}
	
	Vector2 a = Vector2{ (float)input->getMouseX(),(float)input->getMouseY() };
	a = a - m_ray.origin;
	a.normalise();

	if (grapstate != 1) {
		m_ray.direction = a;
	}
	
};