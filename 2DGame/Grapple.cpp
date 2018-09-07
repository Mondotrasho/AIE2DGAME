#include "Grapple.h"
#include "Renderer2D.h"
#include "Grab.h"
#include <glm/detail/func_geometric.inl>
#include "apply_velocity.h"
#include "point_hitcheck.h"

#ifndef PI
#define PI 3.14159265359;
#endif

Grapple::Grapple(Vector2 &origin, Vector2 &direction)
{
	m_length = 250;

	m_ray = { origin, direction, m_length };

	m_rayAngle = atan2(direction.y, direction.x); //remember y then x with atan
	target = nullptr;
	state = 0;
}

Grapple::~Grapple()
{
}

void Grapple::Draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(.3f, .3f, .3f);
	//comfy dot at origin
	renderer->drawCircle((m_ray.origin.x), (m_ray.origin.y), 10);

	//renderer->drawLine(m_ray.origin.x, m_ray.origin.y,		//line
	//	m_ray.origin.x + m_ray.direction.x *m_ray.length,	//starting HERE THIS way by LENGTH
	//	m_ray.origin.y + m_ray.direction.y *m_ray.length,   //starting HERE THIS way by LENGTH
	//	5);

	//velocity Lines for debugging
	renderer->drawLine(m_ray.origin.x, m_ray.origin.y, m_ray.origin.x, m_ray.origin.y + velocity.y);
	renderer->drawLine(m_ray.origin.x, m_ray.origin.y, m_ray.origin.x + velocity.x, m_ray.origin.y);
}

void Grapple::Update(float deltatime, std::vector<Plane>& plane, std::vector<GrapplePoint>& points)
{
	//move
	raycontroller(m_ray, m_rayAngle, velocity, plane[0], deltatime, state);

	//grappling
	//grab check
	Grab(this, deltatime, points);
	if (state == 2) { point_hitcheck(this, points); }
	
	//keep above ground
	for (auto p : plane)
	{
		//top bot
		if (p.N.x == 0 && p.distanceTo(m_ray.origin) < 10)
		{
			velocity.y = -velocity.y + 1;
			//bot
			if (p.N.y == 1)
			{
				
			}
			//top
			if (p.N.y == -1)
			{
				
			}
		}

		//left right
		if (p.N.y == 0 && p.distanceTo(m_ray.origin) < 10)
		{
			velocity.x = -velocity.x + 1;
			//left
			if (p.N.x == 1)
			{
				
			}
			//right
			if (p.N.x == -1)
			{
				
			}
		}


	}
	apply_velocity(*this, velocity, deltatime, 4);
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

void Grapple::raycontroller(Ray& m_ray, float& m_rayAngle, Vector2& velocity, Plane ground, float deltaTime, bool grapstate)
{

	// input example
	aie::Input* input = aie::Input::getInstance();

	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W) && ground.distanceTo(m_ray.origin) < 20) {
		velocity.y += 50;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		//velocity.y -= 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		velocity.x += 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		velocity.x -= 4;
	}

	Vector2 a = Vector2{ (float)input->getMouseX(),(float)input->getMouseY() };
	a = a - m_ray.origin;
	a.normalise();

	if (grapstate != 1) {
		m_ray.direction = a;
	}

};