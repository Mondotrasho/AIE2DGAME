// forward declare GameObject
#pragma once
#include <memory>
#include "Renderer2D.h"

class GameObject;
class Component {
public:
	virtual ~Component() {}
	virtual void update(GameObject* gameObject, float deltaTime) = 0;
	virtual void draw(aie::Renderer2D* renderer) {}
};
//ComponentPtr is a smart-pointer wrapping shared Components​
typedef std::shared_ptr<Component> ComponentPtr;

