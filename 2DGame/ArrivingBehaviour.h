#pragma once
#include "Behaviour.h"
class ArrivingBehaviour :
	public Behaviour
{
public:
	ArrivingBehaviour();
	~ArrivingBehaviour();

	Vector2 update(Object* agent, float deltaTime) override;
	void set_target(Object* target) { m_target = target; }

	Object* m_target;
};

