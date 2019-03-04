#pragma once
#include "../MathsLib/MathsLib/Vector3.h"
#include "Sphere3D.h"

class Plane3D
{
public:
	Plane3D(const Vector3& n, float d) : N(n.normalised()), d(d) {}
	~Plane3D();

	Vector3 N;
	float d;

	bool infrontofplane(const Sphere3D sphere)
	{
		auto newd = N.dot(sphere.position) + d;
		if (newd > 0)
			return  true;
		return false;
	}
};

