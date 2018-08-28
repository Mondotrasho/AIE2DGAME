#pragma once
#include <cmath>
#include "Input.h"
#include "Ray.h"
#include "GrapplePoint.h"

inline void Grab(Grapple* grapps, float deltaTime, std::vector<GrapplePoint>& Targets ,float distance)
{

	// input example
	aie::Input* input = aie::Input::getInstance();
	// use W/S/A/D keys to move ray
	Vector2 intersect_point_sphere;
	Vector2 reflection_sphere;
	
	for (auto& Grappleable : Targets)
	{
		if (grapps->get_ray().intersects(Grappleable.body, &intersect_point_sphere, &reflection_sphere))
		{
			distance = grapps->get_ray().origin.distance(Grappleable.intersect_point);
 			if (input->isKeyDown(aie::INPUT_KEY_SPACE))
			{				
				if (((grapps->get_velocity()* deltaTime) += grapps->get_ray().origin).distance(Grappleable.intersect_point) > distance)
				{
					//switch
					grapps->set_velocity() = { 0,0 };
				}
				if (((grapps->get_velocity()* deltaTime) += grapps->get_ray().origin).distance(Grappleable.intersect_point) < distance)
				{
					//switch
					grapps->set_velocity() = { 0,0 };
				}

				grapps->set_ray().direction.x = sinf(grapps->get_angle());
				grapps->set_ray().direction.y = cosf(grapps->get_angle());
			}
		}
	}
};