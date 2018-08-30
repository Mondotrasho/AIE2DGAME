#pragma once
#include "Plane.h"
#include "Renderer2D.h"

inline void draw_boundries(std::vector<Plane>& plane,aie::Renderer2D* render)
{
	for (auto p : plane)
	{
		// get point on plane closest to window center 
		auto u = p.closestPoint(Vector2(640, 360));
		render->setRenderColour(1, 0, 1);

		// draw plane normal 50 pixels long 
		render->setRenderColour(1, 0, 0);
		render->drawLine(u.x, u.y, u.x + p.N.x * 50, u.y + p.N.y * 50, 4);

		// get a vector perpendicular to the normal 
		Vector2 v(p.N.y, -p.N.x);

		// draw separating line 3000 pixels long 
		render->setRenderColour(1, 1, 0);
		render->drawLine(u.x - v.x * 1500, u.y - v.y * 1500, u.x + v.x * 1500, u.y + v.y * 1500, 4);
	}
	
}
