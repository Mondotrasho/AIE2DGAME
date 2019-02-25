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

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	mouse = new Object(Vector2(0,0),Vector2(0,0),10);
	for (int i = 0; i < 1000; ++i)
	{
		things.push_back(new AutonomousAgent(Vector2(rand() % ((0 - 1280) + 1), rand() % ((0 - 720) + 1)), Vector2(0, 0), 1));
	}
	follow = new FollowBehaviour(1);
	follow->setTarget(mouse);
	for each(auto thing in things)
	{
		thing->addbehaviour(follow);
	}

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
	for each(auto thing in things)
	{
		thing->update(deltaTime);
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void App2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	m_2dRenderer->setRenderColour(0.7, 0.7, 0.2);
	for each(auto thing in things)
	{
		thing->draw(m_2dRenderer);
		m_2dRenderer->drawLine(thing->pos.x, thing->pos.y, thing->pos.x + thing->vel.x * 1, thing->pos.y + thing->vel.y * 1, 1);	}
	
	m_2dRenderer->setRenderColour(0, 1, 0,0.2);
	mouse->draw(m_2dRenderer);
	
	m_2dRenderer->drawText(m_font, ("speed of 1st   : " + std::to_string(things.front()->vel.x) + " : " +std::to_string(things.front()->vel.y)).c_str(), 100, 100);
	//m_2dRenderer->drawText(m_font,("delta   : " + (std::to_string(mouse->pos.x))).c_str() 
	//	, 100, getWindowWidth() / 2 + 100);

	// done drawing sprites
	m_2dRenderer->end();
}
