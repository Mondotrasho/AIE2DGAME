#include "Wraparoundscreen.h"
#include "Object.h"


Wraparoundscreen::Wraparoundscreen()
{
}


Wraparoundscreen::~Wraparoundscreen()
{
}

Vector2 Wraparoundscreen::update(Object* agent, float deltaTime)
{
	if (agent->pos.x > Screen_dimensions.x)
	{
		agent->pos.x = 0;
	}
	if (agent->pos.x < 0)
	{
		agent->pos.x = 1280;
	}
	if (agent->pos.y > Screen_dimensions.y)
	{
		agent->pos.y = 0;
	}
	if (agent->pos.y < 0)
	{
		agent->pos.y = 720;
	}
	return Vector2();
}
