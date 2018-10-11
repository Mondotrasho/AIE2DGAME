#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "IBehaviour.h"

class GameObject {
public:
	GameObject() = default;
	virtual ~GameObject() = default;
	// movement functions
	void setPosition(float x, float y) { m_x = x; m_y = y; }
	void getPosition(float* x, float* y) const { *x = m_x; *y = m_y; }
	void translate(float x, float y) { m_x += x; m_y += y; }
	// add a behaviour
	void addBehaviour(IBehaviour* behaviour);
	// update game object and update behaviours
	virtual void update(float deltaTime);
protected:
	float m_x, m_y;
	std::vector<IBehaviour*> m_behaviours;
};

inline void GameObject::addBehaviour(IBehaviour* behaviour)
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
