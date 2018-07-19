#include "PatrolState.h"
#include "GameObject.h"


PatrolState::PatrolState() : m_currentWaypoint(0)
{}

PatrolState::~PatrolState()
{}

void PatrolState::onUpdate(GameObject* object, float dt)
{
	Vector2 target = m_waypoints[m_currentWaypoint];
	Vector2 pos = object->getPosition();
	Vector2 dist = { target.x - pos.x, target.y - pos.y };
	float mag = sqrt(dist.x * dist.x + dist.y * dist.y);
	if (mag < 50)
	{
		m_currentWaypoint++;
		if (m_currentWaypoint >= m_waypoints.size())
			m_currentWaypoint = 0;
	}
	Vector2 direction = { dist.x / mag, dist.y / mag };
	float speed = object->getSpeed();
	object->setPosition({ pos.x + (direction.x * speed * dt),
		pos.y + (direction.y * speed * dt) });
	float rot = atan2f(direction.y, direction.x);
	object->setRotation(rot);
}