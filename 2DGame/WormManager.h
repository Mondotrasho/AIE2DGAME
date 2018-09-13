#pragma once
#include "Worm.h"

namespace aie {
	class Application;
}

class WormManager
{
public:
	WormManager();
	~WormManager();
	bool Startup(aie::Application& application);
	void shutdown();
	void Update(float deltaTime, std::vector<Plane>& planes);
	void Draw(aie::Renderer2D* render);
	float GetTime() const { return m_timer; }

	void addWorm(aie::Application& application);

	std::vector<Worm> worm_box;

	float m_timer;
};

