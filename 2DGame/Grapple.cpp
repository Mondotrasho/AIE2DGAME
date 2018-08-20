#include "Grapple.h"


Grapple::Grapple(Vector2 &origin, Vector2 &direction)
{
	m_length = 250;

	m_ray = {origin, direction, m_length};

	m_rayAngle = atan2(direction.y, direction.x);

}

Grapple::~Grapple()
{
}

float Grapple::get_angle()
{
	return m_rayAngle;
}

Ray Grapple::get_ray()
{
	return m_ray;
}
