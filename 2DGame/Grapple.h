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
	Grapple() = default;
	Grapple(Vector2 &origin ,Vector2 &direction);
	~Grapple();

	int state; 
	GrapplePoint* target;
	float intercept_distance;
	Vector2 intersect_point;
	Ray m_ray;
	float m_rayAngle;
	float m_length;
	Vector2 velocity;

	void Draw(aie::Renderer2D *renderer);
	void Update(float deltatime, std::vector<Plane>& plane, std::vector<GrapplePoint>& Points);

	float get_angle();
	Ray get_ray();
	float get_angle_deg();

	void raycontroller(Ray& m_ray, float& m_rayAngle, Vector2& velocity, const Plane& ground, float deltaTime, int grapstate);
	void point_hitcheck(Grapple* Player, std::vector<GrapplePoint>& Points);
	void apply_velocity(Grapple& Player, Vector2& velocity, float deltatime, float decay);
	void Grab(Grapple* grapps, float deltaTime, std::vector<GrapplePoint>& Targets);

	Vector2 get_velocity() { return velocity; }
	Vector2& set_velocity() { return velocity; }
	Ray& set_ray() { return m_ray; }
private:
	
	
};

