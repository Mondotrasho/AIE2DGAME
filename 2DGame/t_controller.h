#pragma once
#include "Input.h"

inline void t_controller(float& t_value, float delta_time)
{
	// input example
	aie::Input* input = aie::Input::getInstance();
	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		if (t_value <= 1.0f)t_value += delta_time / 10;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		
		if (t_value >= 0.0f) t_value -= delta_time / 10;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
	
	}

	
};