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

	void Draw(aie::Renderer2D *renderer);
	void Update(float deltatime,Plane& m_plane, std::vector<GrapplePoint>& Points, float distance);

	float get_angle();
	Ray get_ray();
	float get_angle_deg();
	Vector2 get_velocity() { return velocity; }
	Vector2& set_velocity() { return velocity; }
	Ray& set_ray() { return m_ray; }
private:
	Ray m_ray;
	float m_rayAngle;
	float m_length;
	Vector2 velocity;

};

