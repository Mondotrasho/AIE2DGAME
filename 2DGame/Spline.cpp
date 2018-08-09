#include "Spline.h"


Spline::Spline()
{
}


Spline::~Spline()
{
}

Vector3 Spline::getpoint(Vector3 pts[], float t)
{
	Vector3 a = lerp(pts[0], pts[1], t);
	Vector3 b = lerp(pts[1], pts[2], t);
	Vector3 c = lerp(pts[2], pts[3], t);
	Vector3 d = lerp(a, b, t);
	Vector3 e = lerp(b, c, t);

	return lerp(d, e, t);
}

Vector3 Spline::lerp(Vector3& a, Vector3& b, float t)
{
	return a * t + b * (1.f - t);
}

Vector2 Spline::getpoint_2(Vector2 pts[], float t)
{
	Vector2 a = lerp_2(pts[0], pts[1], t);
	Vector2 b = lerp_2(pts[1], pts[2], t);
	Vector2 c = lerp_2(pts[2], pts[3], t);
	Vector2 d = lerp_2(a, b, t);
	Vector2 e = lerp_2(b, c, t);

	return lerp_2(d, e, t);
}

Vector2 Spline::lerp_2(Vector2& a, Vector2& b, float t)
{
	return a * t + b * (1.f - t);
}
