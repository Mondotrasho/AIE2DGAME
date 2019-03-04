#include "Utils.h"
#include "Gizmos.h"
#include "OzGiz.h"
#include "../MathsLib/MathsLib/Vector4.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

void Utils::drawGrid(float height, float width, Vector3 center)
{
	Vector4 white(1, 1, 1, 0.4);
	Vector4 black(0, 0, 0, 0.4);

	for (int i = 0; i <= width; ++i) {
		OzGiz::addLine(Vector3(-10 + i, 0, 10),Vector3(-10 + i, 0, -10),i == 10 ? white : black);
	}
	for (int i = 0; i <= height; ++i) {
		OzGiz::addLine(Vector3(10, 0, -10 + i),Vector3(-10, 0, -10 + i),i == 10 ? white : black);
	}
}
