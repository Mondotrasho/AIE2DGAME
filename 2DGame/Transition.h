#pragma once

class Condition;
class State;
class GameObject;

class Transition final
{
public:
	Transition(Condition* condition, State* target);
	~Transition();

	bool isConditionMet(GameObject* gameObject) const;

	State* getTargetState() const { return m_state; }

private:
	State* m_state;
	Condition* m_condition;
};

