#include "InGameState.h"
#include "GameDefs.h"
#include "PlayerControlledState.h"
#include "PatrolState.h"
#include "ChaseState.h"
#include "WithinRangeCondition.h"
#include "NotCondition.h"
#include "FiniteStateMachine.h"
#include "Transition.h"


void InGameState::onEnter() {
	// set up the player FSM and game object
	FiniteStateMachine* playerFsm = new FiniteStateMachine(1);
	playerFsm->addState(PLAYER_STATE_CONTROLLED, new PlayerControlledState());
	playerFsm->forceState(PLAYER_STATE_CONTROLLED);
	m_player = new GameObject(playerFsm);
	std::shared_ptr<aie::Texture> playerFrame =
		std::make_shared<aie::Texture>("../bin/textures/playerShip1_red.png");
	m_player->addFrame(playerFrame, 1);
	m_player->setPosition({ 150,450 });
	m_player->setSpeed(200);
	// set up the enemy FSM and game object
	PatrolState* patrolState = new PatrolState();
	patrolState->addWaypoint({ 600, 100 });
	patrolState->addWaypoint({ 700, 600 });
	patrolState->addWaypoint({ 1300, 550 });
	patrolState->addWaypoint({ 1200, 150 });
	ChaseState* chaseState = new ChaseState();
	chaseState->setTarget(m_player);
	Condition* inRange = new WithinRangeCondition(m_player, 300);
	Condition* notInRange = new NotCondition(inRange);
	Transition* patrolToChase = new Transition(inRange, chaseState);
	Transition* chaseToPatrol = new Transition(notInRange, patrolState);
	patrolState->addTransition(patrolToChase);
	chaseState->addTransition(chaseToPatrol);
	FiniteStateMachine* enemyFsm = new FiniteStateMachine(2);
	enemyFsm->addState(ENEMY_STATE_PATROL, patrolState);
	enemyFsm->addState(ENEMY_STATE_CHASE, chaseState);
	enemyFsm->forceState(ENEMY_STATE_PATROL);
	m_enemy = new GameObject(enemyFsm);
	std::shared_ptr<aie::Texture> enemyFrame =
		std::make_shared<aie::Texture>("../bin/textures/enemyGreen1.png");
	m_enemy->addFrame(enemyFrame, 1);
	m_enemy->setPosition({ 900, 120 });
	m_enemy->setSpeed(100);
}
void InGameState::onExit() {
	delete m_player;
	delete m_enemy;
}
void InGameState::onUpdate(float deltaTime) {
	m_player->update(deltaTime);
	m_enemy->update(deltaTime);
}
void InGameState::onDraw(aie::Renderer2D* renderer) {
	m_player->draw(renderer);
	m_enemy->draw(renderer);
}