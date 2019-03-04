#pragma once
#include "../MathsLib/MathsLib/Vector3.h"

class Utils
{
public:
	Utils();
	~Utils();

	static void drawGrid(float height,float width,Vector3 center = Vector3(0,0,0));
};

