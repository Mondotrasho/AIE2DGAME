#include "GameStateManager.h"
#include "GameState.h"


void GameStateManager::registerState(int id, GameState* state) {
	m_registeredStates[id] = state;
}
void GameStateManager::pushState(int id) {
	m_pushedStates.push_back(m_registeredStates[id]);
}
void GameStateManager::popState() {
	m_popState = true;
}
void GameStateManager::update(float deltaTime) {
	while (m_popState) {
		m_popState = false;
		// deactivate previous top
		m_stateStack.back()->exit();
		auto temp = m_stateStack.back();
		m_stateStack.pop_back();
		temp->onPopped();
		// activate the one under the previous top
		// if it exists
		if (m_stateStack.empty() == false)
			m_stateStack.back()->enter();
	}
	for (auto pushedState : m_pushedStates) {
		// deactivate previous top
		if (m_stateStack.empty() == false)
			m_stateStack.back()->exit();
		// activate new top
		pushedState->onPushed();
		m_stateStack.push_back(pushedState);
		m_stateStack.back()->enter();
	}
	m_pushedStates.clear();
	for (auto state : m_stateStack)
		state->onUpdate(deltaTime);
}
void GameStateManager::draw(aie::Renderer2D* renderer)
{
	for (auto state : m_stateStack)
		state->onDraw(renderer);
}