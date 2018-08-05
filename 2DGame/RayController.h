#pragma once
#include <cmath>
#include "Input.h"
#include "Ray.h"

inline void raycontroller(Ray& m_ray, float& m_rayAngle, float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();
	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		m_ray.origin.y += 200 * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		m_ray.origin.y -= 200 * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		m_ray.origin.x += 200 * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		m_ray.origin.x -= 200 * deltaTime;
	}
	// use Q/E keys to rotate ray
	if (input->isKeyDown(aie::INPUT_KEY_Q))
		m_rayAngle -= deltaTime;
	if (input->isKeyDown(aie::INPUT_KEY_E))
		m_rayAngle += deltaTime;
	m_ray.direction.x = sinf(m_rayAngle);
	m_ray.direction.y = cosf(m_rayAngle);
};