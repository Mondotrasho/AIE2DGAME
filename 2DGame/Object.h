#pragma once
#include "Vector2.h"
#include "Renderer2D.h"

class Object
{
public:
	Object();
	Object(Vector2 Pos, Vector2 Vel, float Size, float MaxV = 100.0f) : pos(Pos), vel(Vel), size(Size), max_velocity(MaxV){}
	~Object();
	void set_velocity(const Vector2& Vel) { vel = Vel; };
	Vector2 get_velocity() { return vel; };


	Vector2 pos;
	Vector2 vel;
	float size;
	float max_velocity;
	void set_position(Vector2 newpos)
	{
		pos = newpos;
	}
	Vector2 get_position()
	{
		return pos;
	}
	
	void draw(aie::Renderer2D* rend);
	//void update(float deltatime);
	//
};

