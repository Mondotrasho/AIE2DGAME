#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "DebugFunctions.h"
#include <unordered_map>

class App2D : public aie::Application {
public:

	App2D();
	virtual ~App2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();


	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	float m_cameraX = 0;
	float m_cameraY = 0;
	float m_timer = 0;

	DebugFunctions* debug_;

	std::unordered_map<Hex, float>* heights;

	float* Time; //storing delta time
protected:
	//bool createWindow(const char* title, int width, int height, bool fullscreen) override;
	//void destroyWindow() override;

};
