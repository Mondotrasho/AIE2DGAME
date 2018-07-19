#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Snack.h"
#include <list>
#include "SnackFactory.h"

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
 
	std::unique_ptr<SnackFactory> m_snackFactory;
	std::list<std::shared_ptr<Snack>> m_snacks;
};
