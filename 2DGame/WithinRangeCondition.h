#ifndef WITHINRANGECONDITION_H
#define WITHINRANGECONDITION_H
#include "GameObject.h"
#include "Condition.h"

class WithinRangeCondition : public Condition {
public:
	WithinRangeCondition(const GameObject* target, float range)	: m_target(target), m_range(range) {}

	virtual ~WithinRangeCondition() {}

	virtual bool test(GameObject* gameObject) const;

private:

	const GameObject* m_target;
	float m_range;
};

inline bool WithinRangeCondition::test(GameObject* gameObject) const
{
	// get target position
	float tx = 0, ty = 0;
	m_target->getPosition(&tx, &ty);
	// get my position
	float x = 0, y = 0;
	gameObject->getPosition(&x, &y);
	// compare the two and get the distance between them
	float xDiff = tx - x;
	float yDiff = ty - y;
	float distance = sqrtf(xDiff * xDiff + yDiff * yDiff);
	return distance <= m_range;
}
#endif // WITHINRANGECONDITION_H
