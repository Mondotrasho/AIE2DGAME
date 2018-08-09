#pragma once
#include "Vector3.h"
#include "Vector2.h"

class Spline
{
public:
	Spline();
	~Spline();

	static Vector3 getpoint(Vector3 pts[], float t);
	static Vector3 lerp(Vector3& a, Vector3& b, float t);

	static Vector2 getpoint_2(Vector2 pts[], float t);
	static Vector2 lerp_2(Vector2& a, Vector2& b, float t);

};

