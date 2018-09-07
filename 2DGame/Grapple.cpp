#include "Renderer2D.h"
#include "Input.h"
#include "Grapple.h"
#include "GrapplePoint.h"

//Pi for conversions between angles
#ifndef PI
#define PI 3.14159265359;
#endif

Grapple::Grapple(Vector2 &origin, Vector2 &direction)
{
	//the length of the ray check
	m_length = 250;
	//put it and point it
	m_ray = { origin, direction, m_length };
	//point the m_ray angle
	m_rayAngle = atan2(direction.y, direction.x); //remember y then x with atan
												  //empty target
	target = nullptr;
	state = not_grappled;
}

Grapple::~Grapple()
= default;

void Grapple::Draw(aie::Renderer2D* renderer)
{
	//colour
	renderer->setRenderColour(.3f, .3f, .3f);
	//comfy dot at origin
	renderer->drawCircle((m_ray.origin.x), (m_ray.origin.y), 10);

	//Ray for Debugging
	renderer->drawLine(m_ray.origin.x, m_ray.origin.y,		//line
		m_ray.origin.x + m_ray.direction.x *m_ray.length,	//starting HERE THIS way by LENGTH
		m_ray.origin.y + m_ray.direction.y *m_ray.length,   //starting HERE THIS way by LENGTH
		5);

	//velocity Lines for debugging
	renderer->drawLine(m_ray.origin.x, m_ray.origin.y, m_ray.origin.x, m_ray.origin.y + velocity.y);
	renderer->drawLine(m_ray.origin.x, m_ray.origin.y, m_ray.origin.x + velocity.x, m_ray.origin.y);
}

void Grapple::Update(float deltatime, std::vector<Plane>& planes, std::vector<GrapplePoint>& points)
{
	//Call Move
	RayController(m_ray, m_rayAngle, velocity, planes[0], deltatime, state);

	//Grab Collision/ray intercept
	Grab(this, deltatime, points);

	//If state was set by grab to firing then todo Merge Grab and Grapplepoint check
	if (state == firing)
	{
		GrapplePointHitCheck(this, points);
	}

	//Bounce off walls
	Bounce(planes, m_ray, velocity);

	//Apply Velocity
	ApplyVelocity(*this, velocity, deltatime);
}

float Grapple::GetAngleRad()
{
	while (m_rayAngle > 6.283185307) { m_rayAngle -= 6.283185307; }
	return m_rayAngle;
}

Ray Grapple::GetRay() const
{
	return m_ray;
}

float Grapple::GetAngleDeg()
{
	auto temp = 180 / PI;
	while (m_rayAngle > 6.283185307) { m_rayAngle -= 6.283185307; }
	return m_rayAngle * temp;
}

void Grapple::RayController(Ray& m_ray, float& m_rayAngle, Vector2& velocity, const Plane& ground, float deltaTime, int grapstate)
{

	// input example
	aie::Input* input = aie::Input::getInstance();

	// use W/S/A/D keys to move ray
	if (input->isKeyDown(aie::INPUT_KEY_W) && ground.distanceTo(m_ray.origin) < 20) {
		velocity.y += 50;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		velocity.y -= 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		velocity.x += 4;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		velocity.x -= 4;
	}

	Vector2 a = Vector2{ float(input->getMouseX()),float(input->getMouseY()) };
	a = a - m_ray.origin;
	a.normalise();

	if (grapstate != grappled) {
		m_ray.direction = a;
	}

}
void Grapple::GrapplePointHitCheck(Grapple* Player, std::vector<GrapplePoint>& Points)
{
	Vector2 intersect_point_sphere;
	Vector2 reflection_sphere;
	//TODO PROBLEM This grabs the first in the vector NOT the first the grapple would hit
	for (auto& Grappleable : Points)
	{
		if (Player->GetRay().intersects(Grappleable.body, &intersect_point_sphere, &reflection_sphere))
		{
			Player->state = grappled;
			Player->target = &Grappleable;
			Player->intersect_point = intersect_point_sphere;
			auto v = intersect_point_sphere - Player->GetRay().origin;
			Player->set_ray().direction = v.normalised();
			//todo make sure its anchored to the point not the middle
			Player->intercept_distance = v.magnitude();
			return;
		}
	}
}
void Grapple::ApplyVelocity(Grapple& Player, Vector2& velocity, float deltatime)
{
	//find the Vector perpindicular to the players current direction
	auto perpindicular_dir = Vector2(
		-Player.GetRay().direction.y, //Negative of the y
		Player.GetRay().direction.x   //Positive of the X
	).normalised();					  //Make sure to normalise it as its the direction

	//Move by velocity
	Player.set_ray().origin += velocity * deltatime;

	//Decay todo reimpliment
	//velocity -= (velocity * deltatime) / decay;
	velocity.y += deltatime * gravity.y;

	//If grappled
	if (Player.state == grappled)
	{
		//Sets Values to temp for readability
		float distance = Player.GetRay().origin.distance(Player.intersect_point);
		float original_distance = Player.intercept_distance;

		//make sure to update the rays direction
		Vector2 a = Player.intersect_point;
		a = a - Player.GetRay().origin;
		a.normalise();
		Player.set_ray().direction = a;

		//If further away than we were
		if (distance > original_distance)
		{
			//Velocity is correted by projecting it onto the perpindicular vector
			velocity = perpindicular_dir * perpindicular_dir.dot(velocity);
			//Move the player via its origin closer to the intersect point
			//Essentially moves the player x amount off of the collision point
			Player.set_ray().origin = 
				Player.intersect_point -							   //This point minus
				Player.GetRay().direction * Player.intercept_distance; //This direction by the intecept distance
		}
	}
}
void Grapple::Grab(Grapple* grapps, float deltaTime, std::vector<GrapplePoint>& Targets)
{
	aie::Input* input = aie::Input::getInstance();
	//On left click you are firing
	if (input->isMouseButtonDown(0) && grapps->state == not_grappled)
	{
		grapps->state = firing;
	}
	//On not left click
	if (input->isMouseButtonUp(0) && grapps->state == grappled)
	{
		grapps->state = not_grappled;
		grapps->target = nullptr;
	}
};

void Grapple::Bounce(std::vector<Plane>& planes, Ray& m_ray, Vector2& velocity)
{
	//This Function has a lot of junk TODO fix

	//keep above ground
	//Each side of our level
	for (auto plane : planes)
	{
		//top bot
		if (plane.N.x == 0 && plane.distanceTo(m_ray.origin) < 10)
		{
			//bounce y
			velocity.y = -velocity.y + 1;
			//bot
			if (plane.N.y == 1)
			{

			}
			//top
			if (plane.N.y == -1)
			{

			}
		}

		//left right
		if (plane.N.y == 0 && plane.distanceTo(m_ray.origin) < 10)
		{
			//bounce x
			velocity.x = -velocity.x + 1;
			//left
			if (plane.N.x == 1)
			{

			}
			//right
			if (plane.N.x == -1)
			{

			}
		}


	}

}