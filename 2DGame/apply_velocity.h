#pragma once
#include "Vector2.h"

inline void apply_velocity(Grapple* Player,Vector2 velocity, float deltatime,float decay)
{
	//move
	auto perpindicular_dir = Vector2(Player->get_ray().direction.y, Player->get_ray().direction.x).normalised();

	if (Player->get_ray().length > Player->intercept_distance && Player->state == 1)
	{
		velocity = perpindicular_dir * perpindicular_dir.dot(velocity);
		Player->set_ray().origin = Player->intersect_point - (Player->get_ray().direction * Player->intercept_distance);
	}
	Player->set_ray().origin += velocity * deltatime;
	//decay
	velocity -= (velocity * deltatime) / decay;
};