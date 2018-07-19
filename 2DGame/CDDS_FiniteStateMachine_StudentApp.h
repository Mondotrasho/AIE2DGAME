#pragma once

#include "Application.h"
#include "Renderer2D.h"

class GameObject;

class CDDS_FiniteStateMachine_StudentApp : public aie::Application {
public:

	CDDS_FiniteStateMachine_StudentApp();
	virtual ~CDDS_FiniteStateMachine_StudentApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	GameObject*			m_player;
	GameObject*			m_enemy;
};