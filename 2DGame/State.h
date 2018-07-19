#pragma once

#include <vector>

class Transition;
class GameObject;

class State
{
public:
	State();
	virtual ~State();

	virtual void onEnter(GameObject* object) {}
	virtual void onExit(GameObject* object) {}

	virtual void onUpdate(GameObject* object, float dt) = 0;

	void addTransition(Transition* transition);

	State* getNextState(GameObject* gameObject);

protected:
	std::vector<Transition*> m_transitions;
};

