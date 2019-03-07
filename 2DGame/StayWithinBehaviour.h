#pragma once
#include "Behaviour.h"

class StayWithinBehaviour :
	public Behaviour
{
public:
	StayWithinBehaviour();
	~StayWithinBehaviour();

	Vector2 update(Object* agent, float deltaTime) override;

	void set_walls(Vector2 X,Vector2 Y)
	{
		x_axis_limits.Min = X.Min;
		x_axis_limits.Max = X.Max;
		y_axis_limits.Min = Y.Min;
		y_axis_limits.Max = Y.Max;
	}
	Vector2 x_axis_limits;
	Vector2 y_axis_limits;

	float mod = 10; //the modifyier to make staying within a high proprity

};

