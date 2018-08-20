#pragma once

#include "Ray.h"


namespace aie {
	class Renderer2D;
}

class Grapple
{
public:
	Grapple(Vector2 &origin ,Vector2 &direction);
	~Grapple();

	void Draw(aie::Renderer2D());
	void Update(float deltatime);

	float get_angle();
	Ray get_ray();


private:
	Ray m_ray;
	float m_rayAngle;
	float m_length;
};

