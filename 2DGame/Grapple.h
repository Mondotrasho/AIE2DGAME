#pragma once

#include "Ray.h"


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

	int state; //0 == not 1 == is Grappled 2 == firing
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
	void raycontroller(Ray & m_ray, float & m_rayAngle, Vector2 & velocity, Plane ground, float deltaTime, bool grapstate);
	Vector2 get_velocity() { return velocity; }
	Vector2& set_velocity() { return velocity; }
	Ray& set_ray() { return m_ray; }
private:
	
	
};

