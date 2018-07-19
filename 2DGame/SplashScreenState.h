#include "GameState.h"
namespace aie {
	class Texture;
}
class SplashScreenState : public GameState {
public:
	SplashScreenState(float delay = 3.0f) :
		m_timer(0), m_delay(delay), m_logo(nullptr) {}
	~SplashScreenState() {}
	void onUpdate(float deltaTime);
	void onDraw(aie::Renderer2D* renderer);
	void onEnter();
	void onExit();
	void onPushed() {}
	void onPopped() {}
private:
	float m_delay;
	float m_timer;
	aie::Texture* m_logo;
};