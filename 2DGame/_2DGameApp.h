#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Matrix3.h"

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


	aie::Font*	m_font;//FPS FONT
	float m_timer;//DELTA TIME MEMBER VAR
	
	aie::Texture* m_shipTexture;
	Matrix3 m_matrix = Matrix3::identity;
};
