#pragma once
#include "../MathsLib/MathsLib/Vector3.h"
#include <vector>

class AABB3D 
{
public:
	AABB3D(std::vector<Vector3>& points)
	{
		min.x = min.y = min.z = std::numeric_limits<float>::lowest();
		max.x = max.y = max.z = std::numeric_limits<float>::max();

		for each (auto p in points)
		{
			if (p.x < min.x) min.x = p.x;
			if (p.y < min.y) min.y = p.y;
			if (p.z < min.z) min.z = p.z;
			if (p.x > max.x) max.x = p.x;
			if (p.y > max.y) max.y = p.y;
			if (p.z > max.z) max.z = p.z;
		}
	};
	~AABB3D();

	Vector3 min;
	Vector3 max;
};

