#include "Grapple.h"
#include "Renderer2D.h"
#include "RayController.h"
#include "Grab.h"
#include "nicolausYes_easing.h"
#include <glm/detail/func_geometric.inl>
#include "apply_velocity.h"
#include "point_hitcheck.h"

#ifndef PI
#define PI 3.14159265359;
#endif

Grapple::Grapple(Vector2 &origin, Vector2 &direction)
{
	m_length = 250;

	m_ray = {origin, direction, m_length};

	m_rayAngle = atan2(direction.y, direction.x); //remember y then x with atan

}

Grapple::~Grapple()
{
}

void Grapple::Draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(.3f, .3f, .3f);

	renderer->drawCircle((m_ray.origin.x), (m_ray.origin.y), 10); //comfy dot at origin
	renderer->drawLine(m_ray.origin.x, m_ray.origin.y,		//line
		m_ray.origin.x + m_ray.direction.x *m_ray.length,	//starting HERE THIS way by LENGTH
		m_ray.origin.y + m_ray.direction.y *m_ray.length,   //starting HERE THIS way by LENGTH
		5);
}

void Grapple::Update(float deltatime, std::vector<Plane>& plane, std::vector<GrapplePoint>& points)
{
	//fall to ground
	for (auto p : plane)
	{
		
		if (p.N.x == 0 && p.distanceTo(m_ray.origin) > 10)
		{
			velocity.y -= 300 * deltatime;
		}

		/*if (p.N.y == 0 && p.distanceTo(m_ray.origin) > 10)
		{
			velocity.x -= 200 * deltatime;
		}*/
	} 
	;
	
	//move
	raycontroller(m_ray, m_rayAngle, velocity, plane[0], deltatime);

	//grappling
	//grab check
	Grab(this, deltatime, points); 
	if (state == 2) {point_hitcheck(this, points);}
	apply_velocity(this, velocity, deltatime, 4);
	//keep above ground
	for (auto p : plane)
	{
	
		if (p.N.x == 0 && p.distanceTo(m_ray.origin) < 10)
		{
			velocity.y = -velocity.y * 1;
		}
		if (p.N.x == 0 && p.distanceTo(m_ray.origin) < 1)
		{
			m_ray.origin.y = 10; velocity.y = 0;
		}

		if (p.N.y == 0 && p.distanceTo(m_ray.origin) < 10)
		{
			velocity.x = -velocity.x * 1;
		}
		if (p.N.y == 0 && p.distanceTo(m_ray.origin) < 1)
		{
			m_ray.origin.x = 10; velocity.x = 0;
		}
	
	}
}

float Grapple::get_angle()
{
	while (m_rayAngle > 6.283185307) { m_rayAngle -= 6.283185307; }
	return m_rayAngle;
}

Ray Grapple::get_ray()
{
	return m_ray;
}

float Grapple::get_angle_deg()
{
	auto temp = 180 / PI;
	while (m_rayAngle > 6.283185307) { m_rayAngle -= 6.283185307; }
	return m_rayAngle * temp;
}
