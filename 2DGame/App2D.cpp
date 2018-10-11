#include "App2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "AttackState.h"
#include "IdleState.h"
#include "WithinRangeCondition.h"

App2D::App2D() {

}

App2D::~App2D() {

}

bool App2D::startup() {
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_playerBehaviour.setSpeed(400);
	m_player.addBehaviour(&m_playerBehaviour);
	m_player.setPosition(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f);

	m_enemy.addBehaviour(&m_enemyBehaviour);
	m_enemy.setPosition(100, 100);

	// created new states
	auto attackState = new AttackState(&m_player, 150);
	auto idleState = new IdleState();
	// create the condition, setting the player as the target
	auto withinRangeCondition = new WithinRangeCondition(&m_player, 200);
	// create the transition, this will transition to the attack state when the
	// withinRange condition is met
	auto toAttackTransition = new Transition(attackState, withinRangeCondition);
	// add the transition to the idle state
	idleState->addTransition(toAttackTransition);
	// add all the states, conditions and transitions to the FSM (the enemy
	// behaviour)
	m_enemyBehaviour.addState(attackState);
	m_enemyBehaviour.addState(idleState);

	m_enemyBehaviour.addCondition(withinRangeCondition);
	m_enemyBehaviour.addTransition(toAttackTransition);
	// set the current state of the FSM
	m_enemyBehaviour.setCurrentState(idleState);
	return true;
}

void App2D::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void App2D::update(float deltaTime) {

	m_timer += deltaTime;
	m_player.update(deltaTime);
	m_enemy.update(deltaTime);
	// input example
	aie::Input* input = aie::Input::getInstance();



	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void App2D::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);
	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	float x = 0, y = 0;
	// draw player as a green circle
	m_player.getPosition(&x, &y);
	m_2dRenderer->setRenderColour(0, 1, 0);
	m_2dRenderer->drawCircle(x, y, 10);
	// draw enemy as a red circle
	m_enemy.getPosition(&x, &y);
	m_2dRenderer->setRenderColour(1, 0, 0);
	m_2dRenderer->drawCircle(x, y, 10);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}