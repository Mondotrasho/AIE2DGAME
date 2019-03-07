#pragma once
#include "Behaviour.h"
class Wraparoundscreen :
	public Behaviour
{
public:
	Wraparoundscreen();
	~Wraparoundscreen();
	Vector2 update(Object* agent, float deltaTime) override;

	void set_screensize(Vector2 xandy) { Screen_dimensions = xandy; }

	Vector2 Screen_dimensions;
};

