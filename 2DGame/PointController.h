#pragma once
#include "Vector2.h"

inline void pointcontroller(Vector2& point, float delta_time)
{
	// input example
	aie::Input* input = aie::Input::getInstance();
	// use W/S/A/D keys to move orb
	if (input->isKeyDown(aie::INPUT_KEY_I)) {
		point.y += 200 * delta_time;
	}
	if (input->isKeyDown(aie::INPUT_KEY_K)) {
		point.y -= 200 * delta_time;
	}
	if (input->isKeyDown(aie::INPUT_KEY_L)) {
		point.x += 200 * delta_time;
	}
	if (input->isKeyDown(aie::INPUT_KEY_J)) {
		point.x -= 200 * delta_time;
	}
};
