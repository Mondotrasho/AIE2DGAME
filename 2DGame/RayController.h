#pragma once
#include <cmath>
#include "Input.h"
#include "Ray.h"

inline void raycontroller(Ray& m_ray, float& m_rayAngle,Vector2& velocity, Plane ground, float deltaTime)
{
	
	// input example
	aie::Input* input = aie::Input::getInstance();
	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W) && ground.distanceTo(m_ray.origin) < 20) {
		velocity.y += 50;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		velocity.y -= 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		velocity.x += 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		velocity.x -= 4;
	}
	// use Q/E keys to rotate ray
	if (input->isKeyDown(aie::INPUT_KEY_Q))
		m_rayAngle -= deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_E))
		m_rayAngle += deltaTime;
	m_ray.direction.x = sinf(m_rayAngle);
	m_ray.direction.y = cosf(m_rayAngle);
};