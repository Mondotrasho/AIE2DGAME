#pragma once
#include "Input.h"
#include "GrapplePoint.h"

inline void Grab(Grapple* grapps, float deltaTime, std::vector<GrapplePoint>& Targets)
{
	aie::Input* input = aie::Input::getInstance();
	if (input->isMouseButtonDown(0) && grapps->state == 0)
	{	

		grapps->state = 2;				
	}
	if (input->isMouseButtonUp(0) && grapps->state == 1)
	{
		grapps->state = 0;
		grapps->target = nullptr;
	}
};