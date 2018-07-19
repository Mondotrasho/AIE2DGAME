#include "GameObject.h"
#include "FiniteStateMachine.h"
#include <memory>

GameObject::GameObject(FiniteStateMachine* fsm) : m_fsm(fsm), m_position({ 0.0f, 0.0f }), m_rotation(0), m_speed(50)
{
}

GameObject::~GameObject()
{
	delete m_fsm;
}

void GameObject::update(float deltaTime)
{
	if (m_fsm != nullptr)
		m_fsm->update(this, deltaTime);
	
	m_sprite.update(deltaTime);
}

void GameObject::draw(aie::Renderer2D* renderer)
{
	m_sprite.draw(renderer, m_position.x, m_position.y, m_rotation);
}