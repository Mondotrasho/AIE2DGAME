#pragma once
#include <vector>
#include "GameState.h"

//#include "GameState.h"

namespace aie {
	class Renderer2D;
};
class GameStateManager {
public:
	GameStateManager(unsigned int stateCount) {
		m_registeredStates.resize(stateCount);
	}
	~GameStateManager() {
		for (auto state : m_registeredStates) delete state;
	}
	void registerState(int id, GameState* state);
	void pushState(int id);
	void popState();
	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);
	int activeStateCount() const {return m_stateStack.size() + m_pushedStates.size();}
	GameState* getTopState() const { return m_stateStack.back(); }
	GameState* getState(int id) const { return m_registeredStates[id]; }
private:
	std::vector<GameState*> m_pushedStates;
	bool m_popState = false;
	std::vector<GameState*> m_stateStack;
	std::vector<GameState*> m_registeredStates;
};