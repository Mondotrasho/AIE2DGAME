#include "RandomXY.h"
#include <cstdlib>
#include <ctime>


Vector2 RandomXY::random_on_screen() //todo make this change by resolution of the game
{
	//1280, 720
	
	auto x =  100 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1280-100)));// 0 + float(rand()%100 / RAND_MAX) * 1280;//float(rand() % 100.0f) / ((100 / 1280) + 0.1);//float(rand()) / RAND_MAX) * SCREEN_WIDTH
	auto y =  100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (720 - 100)));//0 + float(rand()%100 / RAND_MAX) * 720;//float(rand() % 100) / ((100 / 720) + 0.1);

	return Vector2(x, y);
}

Vector2 RandomXY::random_in_range(float minX, float maxX, float minY, float maxY)
{
	auto x = minX + float(rand() % 100) / ((100 / maxX) + 0.1);
	auto y = minY + float(rand() % 100) / ((100 / maxY) + 0.1);

		return Vector2(x,y );
}
