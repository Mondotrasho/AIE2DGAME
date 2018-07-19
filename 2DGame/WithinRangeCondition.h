#pragma once
#include "Condition.h"
#include "Vector2.h"
#include <cmath>
#include "GameObject.h"

class WithinRangeCondition : public Condition
{
public:
	WithinRangeCondition(GameObject* target, float distance) :
		m_target(target), m_distance(distance) {}
	~WithinRangeCondition() {}
	bool test(GameObject* go) const
	{
		Vector2 target = m_target->getPosition();
		Vector2 pos = go->getPosition();
		Vector2 dist = { target.x - pos.x, target.y - pos.y };
		float length = sqrt(dist.x * dist.x + dist.y * dist.y);
		if (length < m_distance)
			return true;
		return false;
	}
protected:
	GameObject* m_target;
	float m_distance;
};
