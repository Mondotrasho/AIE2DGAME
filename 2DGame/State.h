#ifndef STATE_H
#define STATE_H

#include <vector>

class GameObject;
class Transition;

class State
{
public:
	State() {};
	virtual ~State() {}
	virtual void update(GameObject* agent, float deltaTime) = 0;
	virtual void init(GameObject* agent) {};
	virtual void exit(GameObject* agent) {};
	void addTransition(Transition* transition) {
		m_transitions.push_back(transition);
	}
	Transition* getTriggeredTransition(GameObject* gameObject);
protected:
	std::vector<Transition*> m_transitions;
};
#endif // STATE_H
