#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "SpriteObject.h"

class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	SpriteObject m_tank, m_turret;
};
