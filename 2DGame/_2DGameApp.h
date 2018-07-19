#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "GameStateManager.h"

class GameObject;


class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	static GameStateManager* getGameStateManager() { return &m_gameStateManager; }
protected:
	static GameStateManager m_gameStateManager;

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	float m_timer;//DELTA TIME MEMBER VAR
};
