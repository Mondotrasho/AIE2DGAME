#pragma once
#include "Vector2.h"

inline void pointcontroller(Vector2 mouse, Vector2& point, float delta_time)
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
	
	if(mouse.x < point.x + 30 && mouse.y < point.y + 30 && mouse.x > point.x - 30 && mouse.y > point.y - 30)
	{
		if(input->isMouseButtonDown(0))
		{
			point.x = mouse.x;
			point.y = mouse.y;
		}
	}
};
