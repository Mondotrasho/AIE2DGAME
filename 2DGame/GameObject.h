#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Behaviour.h"

class GameObject {
public:
	GameObject() = default;
	virtual ~GameObject() = default;
	// movement functions
	void setPosition(float x, float y) { m_x = x; m_y = y; }
	void getPosition(float* x, float* y) const { *x = m_x; *y = m_y; }
	void translate(float x, float y) { m_x += x; m_y += y; }
	// add a behaviour
	void addBehaviour(Behaviour* behaviour);
	// update game object and execute behaviours
	virtual void update(float deltaTime);
protected:
	float m_x, m_y;
	std::vector<Behaviour*> m_behaviours;
};

inline void GameObject::addBehaviour(Behaviour* behaviour)
{
	m_behaviours.push_back(behaviour);
}

inline void GameObject::update(float deltaTime)
{
	for (auto behaviour : m_behaviours)
	{
		behaviour->update(this, deltaTime);
	}
}


#endif // GAMEOBJECT_H
