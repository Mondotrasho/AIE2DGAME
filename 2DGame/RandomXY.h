#pragma once

#include "Vector2.h"

class RandomXY
{
public:

	Vector2 random_on_screen(); //temporarily uese default window size 1280, 720
	Vector2 random_in_range(float minX, float maxX, float minY, float maxY);

};

