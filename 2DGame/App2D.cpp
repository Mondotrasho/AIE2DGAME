#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "App2D.h"
#include <list>
#include "imgui.h"
#include "FollowBehaviour.h"

App2D::App2D() {

}

App2D::~App2D() {

}

bool App2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	mouse = new Object(Vector2(0,0),Vector2(0,0),10);
	thing = new AutonomousAgent(Vector2(100, 100), Vector2(0, 0), 10);
	follow = new FollowBehaviour();
	follow->setTarget(mouse);
	thing->addbehaviour(follow);
	return true;
}

void App2D::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void App2D::update(float deltaTime) {
	

	// input example
	aie::Input* input = aie::Input::getInstance();
	mouse->set_position(Vector2(input->getMouseX(), input->getMouseY()));
	thing->update(deltaTime);
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void App2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	m_2dRenderer->setRenderColour(1, 0, 0);
	thing->draw(m_2dRenderer);
	m_2dRenderer->drawLine(thing->pos.x, thing->pos.y, thing->pos.x + thing->vel.x *100, thing->pos.y +thing->vel.y * 100, 1);
	m_2dRenderer->setRenderColour(0, 1, 0,0.2);
	mouse->draw(m_2dRenderer);
	
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);
	//m_2dRenderer->drawText(m_font,("delta   : " + (std::to_string(mouse->pos.x))).c_str() 
	//	, 100, getWindowWidth() / 2 + 100);

	// done drawing sprites
	m_2dRenderer->end();
}
