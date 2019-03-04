#pragma once
#include "../MathsLib/MathsLib/Vector3.h"
#include <vector>
#include "AABB3D.h"

class Sphere3D
{
public:
	Sphere3D(std::vector<Vector3>& points)
	{
		AABB3D tempbox(points);
		position = (tempbox.min + tempbox.max) / 2;
		radius = tempbox.min.distance(position);
	};
	Sphere3D(Vector3 pos , float rad):radius(rad),position(pos){}
	~Sphere3D();

	float radius;
	Vector3 position;
};



