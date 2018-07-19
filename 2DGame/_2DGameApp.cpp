#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "FiniteStateMachine.h"
#include "GameObject.h"
#include "GameDefs.h"
#include "Condition.h"
#include "Transition.h"
#include <memory>
#include "_2DGameApp.h"
#include "PlayerControlledState.h"
#include "PatrolState.h"
#include "ChaseState.h"
#include "WithinRangeCondition.h"
#include "NotCondition.h"
#include "SplashScreenState.h"
#include "InGameState.h"

GameStateManager _2DGameApp::m_gameStateManager((unsigned int)eGameState::STATE_COUNT);

_2DGameApp::_2DGameApp() //m_2dRenderer()//new aie::Renderer2D()), m_font(new aie::Font("../bin/font/consolas.ttf", 32)), m_timer(0)
//m_player(nullptr), m_enemy(nullptr)
{
}


_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = 	new aie::Font("../bin/font/consolas.ttf", 32);
	
	m_timer= 0;

	// set up game state machine
	m_gameStateManager.registerState((unsigned int)eGameState::SPLASH,new SplashScreenState());
	m_gameStateManager.registerState((unsigned int)eGameState::INGAME,new InGameState());
	m_gameStateManager.pushState((unsigned int)eGameState::SPLASH);
	//FiniteStateMachine* playerFsm = new FiniteStateMachine(1);
	//playerFsm->addState(PLAYER_STATE_CONTROLLED, new PlayerControlledState());
	//playerFsm->forceState(PLAYER_STATE_CONTROLLED);
	//m_player = new GameObject(playerFsm);
	//std::shared_ptr<aie::Texture> playerFrame =
	//	std::make_shared<aie::Texture>("../bin/textures/playerShip1_red.png");
	//m_player->addFrame(playerFrame, 1);
	//m_player->setPosition({ 150,450 });
	//m_player->setSpeed(200);


	//// set up the enemy FSM and game object
	//PatrolState* patrolState = new PatrolState();
	//patrolState->addWaypoint({ 600, 100 });
	//patrolState->addWaypoint({ 700, 600 });
	//patrolState->addWaypoint({ 1300, 550 });
	//patrolState->addWaypoint({ 1200, 150 });
	//ChaseState* chaseState = new ChaseState();
	//chaseState->setTarget(m_player);
	//Condition* inRange = new WithinRangeCondition(m_player, 300);
	//Condition* notInRange = new NotCondition(inRange);
	//Transition* patrolToChase = new Transition(inRange, chaseState);
	//Transition* chaseToPatrol = new Transition(notInRange, patrolState);
	//patrolState->addTransition(patrolToChase);
	//chaseState->addTransition(chaseToPatrol);
	//FiniteStateMachine* enemyFsm = new FiniteStateMachine(2);
	//enemyFsm->addState(ENEMY_STATE_PATROL, patrolState);
	//enemyFsm->addState(ENEMY_STATE_CHASE, chaseState);
	//enemyFsm->forceState(ENEMY_STATE_PATROL);
	//m_enemy = new GameObject(enemyFsm);
	//std::shared_ptr<aie::Texture> enemyFrame =
	//	std::make_shared<aie::Texture>("../bin/textures/enemyGreen1.png");
	//m_enemy->addFrame(enemyFrame, 1);
	//m_enemy->setPosition({ 900, 120 });
	//m_enemy->setSpeed(100);

	return true;
	
}

void _2DGameApp::shutdown() {
	/*delete m_player;
	delete m_enemy;*/
	delete m_font;
	delete m_2dRenderer;
}

void _2DGameApp::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (m_gameStateManager.activeStateCount() <= 0) {
		quit();
		return;
	}
	m_gameStateManager.update(deltaTime);
	
	/*m_player->update(deltaTime);
	m_enemy->update(deltaTime);*/
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE)) {
	quit();
}
}

void _2DGameApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_gameStateManager.draw(m_2dRenderer);

	//m_player->draw(m_2dRenderer);
	//m_enemy->draw(m_2dRenderer);
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}