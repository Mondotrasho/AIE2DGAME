#include "RandomXY.h"
#include <cstdlib>


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

Vector2 RandomXY::random_on_edge()
{
	//1280, 720
	//pick entry side
	//0 == left 1 == right 2 == up 3 == down
	auto leftorrightorupordow = rand() / 4;

	//if left
	if (leftorrightorupordow == 0)
	{
		auto x = 80;
		auto y = 100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (720 - 100)));
		return Vector2(x, y);
	}
	if (leftorrightorupordow == 1)
	{
		auto x = 1200;
		auto y = 100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (720 - 100)));
		return Vector2(x, y);
	}
	//if up
	if (leftorrightorupordow == 2)
	{
		auto x = 100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1280 - 100)));
		auto y = 700;
		return Vector2(x, y);
	}
	if (leftorrightorupordow == 3)
	{
		auto x = 100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1280 - 100)));
		auto y = 20;
		return Vector2(x, y);
	}
	
	
}
