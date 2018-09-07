#pragma once
#include "Vector2.h"

inline void apply_velocity(Grapple& Player,Vector2& velocity, float deltatime,float decay)
{
	Vector2 gravity = { 0,-200 };

	auto perpindicular_dir = Vector2(-Player.get_ray().direction.y, Player.get_ray().direction.x).normalised();
	Player.set_ray().origin += velocity * deltatime;
	//decay
	//velocity -= (velocity * deltatime) / decay;
	velocity.y += deltatime * gravity.y;
	//velocity.y -= 200 * deltatime;
	//move
	
	//if grappled  and the length of the r
	if (Player.state == 1)
	{
		float distance = Player.get_ray().origin.distance(Player.intersect_point);
		float original_distance = Player.intercept_distance;

		Vector2 a = Player.intersect_point;
		a = a - Player.get_ray().origin;
		a.normalise();
		Player.set_ray().direction = a;
		

		if (distance > original_distance)
		{
			velocity = perpindicular_dir * perpindicular_dir.dot(velocity);
			Player.set_ray().origin = Player.intersect_point - Player.get_ray().direction * Player.intercept_distance;

		}
	}
};