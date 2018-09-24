#include "WormManager.h"
#include "Application.h"
#include <cassert>
#include <iostream>
#include <fstream>


WormManager::WormManager() : m_timer(0)
{
}


WormManager::~WormManager()
{
}

bool WormManager::Startup(aie::Application& application,float difficulty)
{
	//CHECK FILE exists
	std::string filename = "../bin/textures/snake_head.png";
	std::ifstream src(filename.c_str());

	std::string filename2 = "../bin/textures/snake_bod.png";
	std::ifstream src2(filename.c_str());
	if (src && src2)
	{
		src.close();
		src2.close();
		for (int i = 0; i < difficulty; ++i)
		{
			worm_box.push_back(Worm());
		}

		for (auto& worm : worm_box)
		{
			worm.setup("../bin/textures/snake_head.png", "../bin/textures/snake_bod.png");

			// center the Worm
			worm.setPosition(application.getWindowWidth() / 2.f, application.getWindowHeight() / 2.f);
			worm.worm_face.center = Vector2(application.getWindowWidth() / 2.f, application.getWindowHeight() / 2.f);
			worm.worm_face.radius = 30;
			worm.worm_states = 0;
		}
	}
	else
	{
		//the textures are not there
		assert(0);
	}
	return true;
}

void WormManager::Update(float deltaTime, std::vector<Plane>& planes)
{
	m_timer += deltaTime;

	if (m_timer > 2.0f)//0.5f)
	{
		m_timer = 0;
		for (auto& worm : worm_box)
		{
			worm.worm_states = (rand() % 3);
		}
	}

	for (auto& worm : worm_box)
	{
		worm.onUpdate(deltaTime, planes);
		worm.worm_face.center.x = worm.getGlobalTransform().translation.x;
		worm.worm_face.center.y = worm.getGlobalTransform().translation.y;
	}


}

void WormManager::Draw(aie::Renderer2D* render)
{
	for (auto& worm : worm_box)
	{
		worm.draw(render);
	}
}

