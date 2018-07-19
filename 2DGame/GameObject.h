#pragma once
#include <memory>
#include "AnimatedSprite.h"
#include "Vector2.h"

class FiniteStateMachine;

namespace aie {
	class Renderer2D;
}

class GameObject
{
public:
	GameObject(FiniteStateMachine* fsm);
	~GameObject();

	void addFrame(const std::shared_ptr<aie::Texture>& frame, float delay) { m_sprite.addFrame(frame, delay); }
	
	Vector2 getPosition() { return m_position; }
	float getRotation() { return m_rotation; }
	float getSpeed() { return m_speed; }

	void setPosition(const Vector2& pos) { m_position = pos; }
	void setRotation(float rot) { m_rotation = rot; }
	void setSpeed(float speed) { m_speed = speed; }

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);

private:
	FiniteStateMachine*		m_fsm;
	AnimatedSprite			m_sprite;
	Vector2			        m_position;
	float					m_rotation;
	float					m_speed;
};

