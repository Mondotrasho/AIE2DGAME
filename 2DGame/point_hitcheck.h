#pragma once
#include "Grapple.h"
#include "GrapplePoint.h"

inline void point_hitcheck(Grapple* Player, std::vector<GrapplePoint>& Points)
{
	Vector2 intersect_point_sphere;
	Vector2 reflection_sphere;
	for (auto& Grappleable : Points)
	{
		if (Player->get_ray().intersects(Grappleable.body, &intersect_point_sphere, &reflection_sphere))
		{
			Player->state = 1;
			Player->target = &Grappleable;
			Player->intersect_point = intersect_point_sphere;
			auto v = intersect_point_sphere - Player->get_ray().origin;
			Player->set_ray().direction = v.normalised();
			//todo make sure its anchored to the point not the middle
			Player->intercept_distance = v.magnitude();
			return;
		}
	}
};