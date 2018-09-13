#include "WormManager.h"
#include "Application.h"
#include "RandomXY.h"


WormManager::WormManager() : m_timer(0) , m_spawn_timer(0)
{
}


WormManager::~WormManager()
= default;

bool WormManager::Startup(aie::Application& application)
{

	//worm_box.push_back(Worm());
	

	for (auto& worm : worm_box)
	{
		worm.setup("../bin/textures/snake_head.png", "../bin/textures/snake_bod.png");

		// center the Worm
		worm.setPosition(application.getWindowWidth() / 2.f, application.getWindowHeight() / 2.f);
		worm.worm_face.center = Vector2(application.getWindowWidth() / 2.f, application.getWindowHeight() / 2.f);
		worm.worm_face.radius = 30;
		worm.worm_states = 0;
		worm.done = true;
	}
	return true;
}
void WormManager::adder(aie::Application& application)
{
	worm_box.push_back(Worm());
	worm_box.back().setup("../bin/textures/snake_head.png", "../bin/textures/snake_bod.png");
	worm_box.back().setPosition(application.getWindowWidth() / 2.f, application.getWindowHeight() / 2.f);
	worm_box.back().worm_face.center = Vector2(application.getWindowWidth() / 2.f, application.getWindowHeight() / 2.f);
	worm_box.back().worm_face.radius = 30;
	worm_box.back().worm_states = 0;
	worm_box.back().done = true;
	
}
void WormManager::Update(float deltaTime, std::vector<Plane>& planes, aie::Application& application)
{
	m_timer += deltaTime;
	m_spawn_timer += deltaTime;
	if (m_timer > 2.0f)//0.5f)
	{
		m_timer = 0;
		for (auto& worm : worm_box)
		{
			worm.worm_states = (rand() % 3);
		}
	}
	//todo add add worm to update when delta time > x create new worm
	if (m_spawn_timer > 10.0f)//0.5f)
	{
		m_spawn_timer = 0;
		//addWorm(application);
	}
		
	

	for (auto worm : worm_box)
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

//void WormManager::addWorm(aie::Application& application)
//{
//	auto worm = new Worm();
//
//	
//	worm->setup("../bin/textures/snake_head.png", "../bin/textures/snake_bod.png");
//
//	RandomXY randomer;
//	auto temp = randomer.random_on_edge();
//	// center the Worm
//	worm->setPosition(temp.x, temp.y);
//	worm->worm_face.center = Vector2(temp.x, temp.y);
//	worm->worm_face.radius = 30;
//	worm->worm_states = 0;
//	worm_box.push_back(*worm);
//}


