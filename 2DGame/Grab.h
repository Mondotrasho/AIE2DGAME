#pragma once
#include <cmath>
#include "Input.h"
#include "Ray.h"
#include "GrapplePoint.h"

inline void Grab(Ray& m_ray, float& m_rayAngle, float deltaTime, std::vector<GrapplePoint>& Targets ,float distance)
{

	// input example
	aie::Input* input = aie::Input::getInstance();
	// use W/S/A/D keys to move ray
	
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		
		for (auto& Grappleable : Targets)
		{
			Vector2 intersect_point_sphere;
			Vector2 reflection_sphere;
			if (m_ray.intersects(Grappleable.body, &intersect_point_sphere, &reflection_sphere))
			{
				distance = m_ray.origin.distance(Grappleable.intersect_point);
        		if (m_ray.origin.distance(Grappleable.intersect_point) > distance && input->isKeyDown(aie::INPUT_KEY_SPACE))
				{
					//switch
					m_ray.origin -= 1;\
				}
			}
			m_ray.direction.x = sinf(m_rayAngle);
			m_ray.direction.y = cosf(m_rayAngle);
		}
	}
};