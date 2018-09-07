#pragma once
#include "Ray.h"

enum state
{	not_grappled,
	grappled,
	firing
};

class GrapplePoint;

namespace aie {
	class Renderer2D;
}

class Grapple
{
public:
	//Con and De Structors
	Grapple() = default;
	Grapple(Vector2 &origin ,Vector2 &direction);
	~Grapple();

	//Main
	void Draw(aie::Renderer2D *renderer);
	void Update(float deltatime, std::vector<Plane>& plane, std::vector<GrapplePoint>& Points);

	//Angle stuff
	float GetAngleRad();
	Ray GetRay() const;
	float GetAngleDeg();

	//Controls
	void RayController(Ray& m_ray, float& m_rayAngle, Vector2& velocity, const Plane& ground, float deltaTime, int grapstate);
	void GrapplePointHitCheck(Grapple* Player, std::vector<GrapplePoint>& Points);
	void Grab(Grapple* grapps, float deltaTime, std::vector<GrapplePoint>& Targets);

	

	//Velocity management
	void ApplyVelocity(Grapple& Player, Vector2& velocity, float deltatime);
	Vector2 GetVelocity() { return velocity; }
	Vector2& SetVelocity() { return velocity; }
	void Bounce(std::vector<Plane>& planes, Ray & m_ray, Vector2 & velocity);

	//The core of the player
	Ray& set_ray() { return m_ray; }


	//Variables todo make not public LOT OF WORK
	//Player state and target info
	int state;
	GrapplePoint* target;
	float intercept_distance;
	Vector2 intersect_point;
	//The Body
	Ray m_ray;
	float m_rayAngle;
	float m_length; //todo make this changable on construction
	//Velocity
	Vector2 velocity;
	Vector2 gravity = { 0,-200 }; //todo make this changable on construction
	Vector2 decay = { 0,0 }; //todo make this changable on construction
};

