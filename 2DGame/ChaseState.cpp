#include "ChaseState.h"
#include "Vector2.h"
#include "GameObject.h"


ChaseState::ChaseState(): m_target(nullptr)
{
}


ChaseState::~ChaseState()
{
}

void ChaseState::onUpdate(GameObject* object, float dt)
{
	Vector2 target = m_target->getPosition();
	Vector2 pos = object->getPosition();

	Vector2 dist = { target.x - pos.x, target.y - pos.y };
	float mag = sqrt(dist.x * dist.x + dist.y * dist.y);


	Vector2 direction = { dist.x / mag, dist.y / mag };
	float speed = object->getSpeed();
	object->setPosition({ pos.x + (direction.x * speed * dt),
		pos.y + (direction.y * speed * dt) });
	float rot = atan2f(direction.y, direction.x);
	object->setRotation(rot);
	
}

