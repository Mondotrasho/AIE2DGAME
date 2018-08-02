#pragma once
#include "Component.h"
#include <vector>
#include "SpriteObject.h"

class GameObject {
public:
	GameObject() {}
	virtual ~GameObject() {}
	//updateComponent
	virtual void update(float deltaTime) {
		for (auto& component : m_components)
			//tell the component to update this gameobject
			component->update(this, deltaTime);
	}
	
	void addComponent(const ComponentPtr& component) {
		m_components.push_back(component);
	}
	//drawcomponent
	virtual void draw() {
		for (auto& component : m_components)
			component->draw(this);
	}
private:
	SpriteObject m_sprite;
protected:
	std::vector< ComponentPtr > m_components;
};
