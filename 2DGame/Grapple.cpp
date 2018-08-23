#include "Grapple.h"
#include "Renderer2D.h"
#include "RayController.h"


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

void Grapple::Update(float deltatime,Plane& plane)
{
	//todo fix
	//fall to ground
	if(plane.distanceTo(m_ray.origin) > 10){m_ray.origin.y -= 200 * deltatime; }
	//move
	raycontroller(m_ray, m_rayAngle, deltatime);
	//keep above ground
	if (plane.distanceTo(m_ray.origin) < 10) { m_ray.origin.y = 10; }
}

float Grapple::get_angle()
{
	return m_rayAngle;
}

Ray Grapple::get_ray()
{
	return m_ray;
}
