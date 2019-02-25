#pragma once
#include "Vector2.h"
#include "Renderer2D.h"

class Object
{
public:
	Object();
	Object(Vector2 Pos, Vector2 Vel, float Size, float MaxV = 30.0f,Vector2 Acc = Vector2(1,1)) : pos(Pos), vel(Vel), size(Size), max_velocity(MaxV), acc(Acc) {}
	~Object();
	void set_velocity(const Vector2& Vel) { vel = Vel; };
	Vector2 get_velocity() { return vel; };


	Vector2 pos;
	Vector2 vel;
	Vector2 acc;
	float size;
	float max_velocity;
	float speed = 1;
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

