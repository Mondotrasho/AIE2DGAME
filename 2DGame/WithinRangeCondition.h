#ifndef WITHINRANGECONDITION_H
#define WITHINRANGECONDITION_H
#include "GameObject.h"
#include "Condition.h"

class WithinRangeCondition : public Condition {
public:
	WithinRangeCondition(const Agent* target, float range)	: m_target(target), m_range(range) {}

	virtual ~WithinRangeCondition() {}

	virtual bool test(Agent* agent) const;

private:

	const Agent* m_target;
	float m_range;
};

inline bool WithinRangeCondition::test(Agent* agent) const
{
	// get target position
	Vector2 targetpos = m_target->getPosition();
	// get my position
	Vector2 myPos = agent->getPosition();
	// compare the two and get the distance between them
	float xDiff = targetpos.x - myPos.x;
	float yDiff = targetpos.y - myPos.y;
	float distance = sqrtf(xDiff * xDiff + yDiff * yDiff);
	return distance <= m_range;
}
#endif // WITHINRANGECONDITION_H
