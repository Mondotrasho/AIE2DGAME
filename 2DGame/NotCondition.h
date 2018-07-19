#pragma once
#include "Condition.h"
class NotCondition : public Condition {
public:
	NotCondition(Condition* condition) : m_condition(condition) {}
	virtual ~NotCondition() {}
	virtual bool test(GameObject* go) const {
		return !m_condition->test(go);
	}
protected:
	Condition* m_condition;
};

