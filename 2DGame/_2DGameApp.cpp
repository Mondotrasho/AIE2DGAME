

#include "_2DGameApp.h"
#include "Font.h"
#include "RandomXY.h"
#include <ctime>
#include "Curves.h"
#include "Input.h"
#include "LevelManager.h"
#include <winerror.h>
#include <iostream>
#include <fstream>

_2DGameApp::_2DGameApp()
{
}

_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {

	srand(time(NULL));

	m_2dRenderer = new aie::Renderer2D();

	//Temp variables for readability
	Vector2 startypoint = { 640, 360 }; // X = 640 Y = 360
	Vector2 directionypoint = { 0.7f, 0.7f }; //start pointing up 0.7 of the way and across 0.7 of the way

	//CHECK FILE exists
	std::string filename = "../bin/font/consolas.ttf";
	std::ifstream src(filename.c_str());
	if (src)
	{
		src.close();
		m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	}
	else
	{	//the textures are not there
		assert(0);
	}
	

	m_timer = 0;
	m_timer2 = 0;
	auto temp = Vector2(startypoint.x - 300, startypoint.y);
	player = { temp, directionypoint};

	RandomXY randomer;

	for (int i = 0; i < 15; ++i)
	{
		box.push_back(GrapplePoint(randomer.random_on_screen(), 30)); // random_in_range(50, 1280 - 50, 50, 720 - 50), 30));
	}

	Ground = { Vector2(1, 3),Vector2(2,3) };//{ Vector2(0.0f,0.1f),-50 }; //use this format for rotating as the 0.1 0.2 etc is easier for for loops and shite
	Roof = { Vector2(2, getWindowHeight() - 3),Vector2(1,getWindowHeight() - 3) };
	Right = { Vector2(getWindowWidth() - 3, 1),Vector2(getWindowWidth() - 3,2) };
	Left = { Vector2(3, 2),Vector2(3,1) };
	
	walls.push_back(Ground);
	walls.push_back(Right);
	walls.push_back(Roof);
	walls.push_back(Left);
	difficulty = 10.0f;
	worm_manager.Startup(*this,difficulty);

	end = false;

	return true;
	
}

void _2DGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}




void _2DGameApp::update(float deltaTime) {

	m_timer += deltaTime;
	if (!end) {
		m_timer2 += deltaTime;
	}

	level.RandomizeColours(deltaTime);
	
	player.Update(deltaTime, walls, box);

	if (m_timer > difficulty)//0.5f)
	{
		for (auto& worm : worm_manager.worm_box)
		{
			worm.velocity.x += 1.0f;
			worm.velocity.y += 1.0f;
		}
		difficulty += difficulty;
	}
	for (auto &worm : worm_manager.worm_box)
	{
		if(worm.checkCollision(player.m_ray.origin))
		{
			end = true;
		}
	}

	//difficulty
	worm_manager.Update(deltaTime, walls);

	// input example
	aie::Input* input = aie::Input::getInstance();
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _2DGameApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	//back drop
	m_2dRenderer->setRenderColour(0.5, 0.5, 0.5);
	m_2dRenderer->drawBox(getWindowWidth() / 2, getWindowHeight() / 2, getWindowWidth(), getWindowHeight(), 0, 100);
	
	//m_2dRenderer->setRenderColour(level.GetRed(),level.GetGreen(),level.GetBlue());
	m_2dRenderer->setRenderColour(0.5, 0.5, 1);

	player.Draw(m_2dRenderer);

	worm_manager.Draw(m_2dRenderer);

	Vector2 intersect_point_sphere;
	Vector2 reflection_sphere;


	auto rad = player.GetAngleRad();
	auto deg = player.GetAngleDeg();

	float t = 0;

	for (auto& Grappleable : box)
	{
		Grappleable.Draw(m_2dRenderer);

		if (player.state == grappled) //player.GetRay().intersects(Grappleable.body, &intersect_point_sphere, &reflection_sphere) &&
		{
			m_2dRenderer->setRenderColour(.9f, .8f, .3f);
			//m_2dRenderer->drawCircle((intersect_point_sphere.x), (intersect_point_sphere.y), 10);
			auto temp1 = Vector2(intersect_point_sphere.x, intersect_point_sphere.y - 100);

			vecs.push_back(player.intersect_point);
			if (player.GetAngleDeg() > 180) {
				vecs.push_back(Vector2(player.intersect_point.x + (reflection_sphere.x / 2), player.intersect_point.y - (player.GetRay().origin.distance(player.intersect_point)) / 4));
			}
			else
			{
				vecs.push_back(Vector2(player.intersect_point.x - (reflection_sphere.x / 2), player.intersect_point.y - (player.GetRay().origin.distance(player.intersect_point)) / 4));
			}

			vecs.push_back(player.GetRay().origin);


			Vector2 first = Curves::CardinalSpline(vecs.data(), vecs.size(), 1 / 50.0f, 0.001);
			for (double i = 0; i < 100; ++i)
			{
				Vector2 secnd = Curves::CardinalSpline(vecs.data(), vecs.size(), i / 50.0f, 0.5);

				m_2dRenderer->drawLine(first.x, first.y, secnd.x, secnd.y, 1);

				first = secnd;

			}
			m_2dRenderer->setRenderColour(1, 0, 0);
			//	m_2dRenderer->drawCircle(vecs[0].x, vecs[0].y, 2);
			//	m_2dRenderer->setRenderColour(0, 1, 0);
				//m_2dRenderer->drawCircle(vecs[1].x, vecs[1].y, 2);
			m_2dRenderer->setRenderColour(0, 0, 1);
			//	m_2dRenderer->drawCircle(vecs[2].x, vecs[2].y, 2);



			vecs.clear();
			auto temp = reflection_sphere + intersect_point_sphere;
			//m_2dRenderer->drawLine((intersect_point_sphere.x), (intersect_point_sphere.y), temp.x, temp.y);


		}
	}

	
	//m_2dRenderer->drawCircle(worm.worm_face.center.x, worm.worm_face.center.y, worm.worm_face.radius);
	//level.draw_boundries(walls, m_2dRenderer,*this);
	m_2dRenderer->setRenderColour(0, 0, 0);

	char Score[32];
	std::string s = std::to_string(int(m_timer2));
	char cstr[32];
	strcpy(cstr, s.c_str());
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, cstr, 30, 720 - 100);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "SCORE", 100, 720 - 100);
	if (end)
	{
		char Score[32];
		std::string s = std::to_string(int(m_timer2));
		char cstr[32];
		strcpy(cstr, s.c_str());
		m_2dRenderer->setRenderColour(0.4f, 0, 0);

		m_2dRenderer->drawText(m_font, "GAME OVER", getWindowWidth() / 2 - 40, (getWindowHeight() / 2) + 30);
		m_2dRenderer->drawText(m_font, "FINAL SCORE", getWindowWidth() / 2 - 40, getWindowHeight() / 2);
		m_2dRenderer->drawText(m_font, cstr, getWindowWidth() / 2 , (getWindowHeight() / 2) - 30);
		
	}
	// done drawing sprites
	m_2dRenderer->end();
}

