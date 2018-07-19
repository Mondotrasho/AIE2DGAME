#pragma once
#include "GameObject.h"
#include "GameState.h"

class InGameState : public GameState
{
public:
	InGameState() {}
	~InGameState() {}
	void onUpdate(float deltaTime);
	void onDraw(aie::Renderer2D* renderer);
	void onEnter();
	void onExit();
	void onPushed() {}
	void onPopped() {}
private:
	GameObject* m_player;
	GameObject* m_enemy;
};
