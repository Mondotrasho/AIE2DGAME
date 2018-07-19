#include "SplashScreenState.h"
#include "GameDefs.h"
#include "_2DGameApp.h"
#include "Texture.h"


void SplashScreenState::onEnter() {
	m_logo = new aie::Texture("../bin/textures/AIE.png");
}
void SplashScreenState::onExit() {
	delete m_logo;
	m_logo = nullptr;
}
void SplashScreenState::onUpdate(float deltaTime) {
	m_timer += deltaTime;
	if (m_timer > m_delay) {
		GameStateManager* gm = _2DGameApp::getGameStateManager();
		gm->popState();
		gm->pushState((unsigned int)eGameState::INGAME);
	}
}
void SplashScreenState::onDraw(aie::Renderer2D* renderer) {
	if (m_logo) {
		renderer->setRenderColour(0.04296875f, 0.109375f, 0.1640625f);
		renderer->drawBox(640, 360, 1280, 720);
		renderer->setRenderColour(1, 1, 1);
		renderer->drawSprite(m_logo, 640, 360);
	}
}