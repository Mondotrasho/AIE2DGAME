#include "RandomXY.h"
#include <cstdlib>


Vector2 RandomXY::random_on_screen() //todo make this change by resolution of the game
{
	//1280, 720
	auto x = 0 + float(rand() % 100) / ((100 / 1280) + 0.1);
	auto y = 0 + float(rand() % 100) / ((100 / 720) + 0.1);

	return Vector2(x, y);
}

Vector2 RandomXY::random_in_range(float minX, float maxX, float minY, float maxY)
{
	auto x = minX + float(rand() % 100) / ((100 / maxX) + 0.1);
	auto y = minY + float(rand() % 100) / ((100 / maxY) + 0.1);

		return Vector2(x,y );
}
