#pragma once

#include "Ray.h"


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
	void Update(float deltatime,Plane& m_plane);

	float get_angle();
	Ray get_ray();


private:
	Ray m_ray;
	float m_rayAngle;
	float m_length;
};

