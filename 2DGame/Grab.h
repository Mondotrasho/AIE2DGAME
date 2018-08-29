#pragma once
#include "Input.h"
#include "GrapplePoint.h"

inline void Grab(Grapple* grapps, float deltaTime, std::vector<GrapplePoint>& Targets)
{
	aie::Input* input = aie::Input::getInstance();
	
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{	
		grapps->state = 2;				
	}
	if (input->isKeyUp(aie::INPUT_KEY_SPACE) && grapps->state != 2)
	{
		grapps->state = 0;
		grapps->target = nullptr;
	}
};