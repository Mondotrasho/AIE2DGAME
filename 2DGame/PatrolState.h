#pragma once
#include "State.h"
#include "Vector2.h"
#include <vector>
class PatrolState : public State
{
public:
	PatrolState();
	~PatrolState();
	void onUpdate(GameObject* object, float dt);
	void addWaypoint(Vector2 pos) { m_waypoints.push_back(pos); }
private:
	std::vector<Vector2> m_waypoints;
	int m_currentWaypoint;
};

