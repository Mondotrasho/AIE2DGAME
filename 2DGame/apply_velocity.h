#pragma once
#include "Vector2.h"

inline void apply_velocity(Grapple& Player,Vector2& velocity, float deltatime,float decay)
{
	
	
	Player.set_ray().origin += velocity * deltatime;
	//decay
	velocity -= (velocity * deltatime) / decay;

	//move
	auto perpindicular_dir = Vector2(Player.get_ray().direction.y, Player.get_ray().direction.x).normalised();
	//if grappled  and the length of the r
	if (Player.state == 1)
	{
		auto distance = Player.get_ray().origin.distance(Player.intersect_point);
		auto original_distance = Player.intercept_distance;

		if (distance > original_distance)
		{
			velocity = perpindicular_dir * perpindicular_dir.dot(velocity);
			Player.set_ray().origin = Player.target->intersect_point - (Player.get_ray().direction * Player.intercept_distance);
		}
	}
};