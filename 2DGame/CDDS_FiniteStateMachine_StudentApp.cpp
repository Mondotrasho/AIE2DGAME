#include "CDDS_FiniteStateMachine_StudentApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "FiniteStateMachine.h"
#include "GameObject.h"
#include "GameDefs.h"
#include "Condition.h"
#include "Transition.h"
#include <memory>

CDDS_FiniteStateMachine_StudentApp::CDDS_FiniteStateMachine_StudentApp() : 
	m_player(nullptr), m_enemy(nullptr)
{
}

CDDS_FiniteStateMachine_StudentApp::~CDDS_FiniteStateMachine_StudentApp() {

}

bool CDDS_FiniteStateMachine_StudentApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void CDDS_FiniteStateMachine_StudentApp::shutdown() {
	delete m_player;
	delete m_enemy;
	delete m_font;
	delete m_2dRenderer;
}

void CDDS_FiniteStateMachine_StudentApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void CDDS_FiniteStateMachine_StudentApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}