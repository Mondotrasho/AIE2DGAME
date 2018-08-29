

#include "_2DGameApp.h"
#include "Font.h"
#include "RayController.h"
#include "PointController.h"
#include "RandomXY.h"
#include <ctime>
#include "Curves.h"

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

	m_colour = { 0.3f,0.7f,0.0f };

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_timer = 0;

	player = { startypoint, directionypoint};

	RandomXY randomer;

	for (int i = 0; i < 15; ++i)
	{
		box.push_back(GrapplePoint(randomer.random_on_screen(), 30));
	}

	m_plane = { Vector2(400, 3),Vector2(401,3) };//{ Vector2(0.0f,0.1f),-50 }; //use this format for rotating as the 0.1 0.2 etc is easier for for loops and shite
	return true;
}

void _2DGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}




void _2DGameApp::update(float deltaTime) {

	m_timer += deltaTime;
	//colour changing todo move
	//0.0 - 1.0
	m_colour.R += deltaTime / 2;
	if (m_colour.R > 1) { m_colour.R = 0; }
	m_colour.G += deltaTime / 2;
	if (m_colour.G > 1) { m_colour.G = 0; }
	m_colour.B += deltaTime / 2;
	if (m_colour.B > 1) { m_colour.B = 0; }
	//END COLOUR
	player.Update(deltaTime, m_plane, box);
	
	
	
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
	m_2dRenderer->setRenderColour(m_colour.R, m_colour.G, m_colour.B);
	player.Draw(m_2dRenderer);

	Vector2 intersect_point_sphere;
	Vector2 reflection_sphere;


	auto rad = player.get_angle();
	auto deg = player.get_angle_deg();

	float t = 0;
	
	for (auto& Grappleable : box)
	{
		Grappleable.Draw(m_2dRenderer, test);
		
		if (player.get_ray().intersects(Grappleable.body, &intersect_point_sphere, &reflection_sphere))
		{
			m_2dRenderer->setRenderColour(.3f, .3f, .3f);
			m_2dRenderer->drawCircle((intersect_point_sphere.x), (intersect_point_sphere.y), 10);
			auto temp1 = Vector2(intersect_point_sphere.x, intersect_point_sphere.y - 100);
			
			vecs.push_back(intersect_point_sphere);
			if (player.get_angle_deg() > 180) {
				vecs.push_back(Vector2(intersect_point_sphere.x + (reflection_sphere.x / 2), intersect_point_sphere.y - (player.get_ray().origin.distance(intersect_point_sphere)) / 4));
			}
			else
			{
				vecs.push_back(Vector2(intersect_point_sphere.x - (reflection_sphere.x / 2), intersect_point_sphere.y - (player.get_ray().origin.distance(intersect_point_sphere)) / 4));
			}

				vecs.push_back(player.get_ray().origin);


			Vector2 first = Curves::CardinalSpline(vecs.data(),vecs.size(), 1 / 50.0f, 0.001);
			for (double i = 0; i < 100; ++i)
			{
				Vector2 secnd = Curves::CardinalSpline(vecs.data(), vecs.size(), i / 50.0f,	0.5);
				
				m_2dRenderer->drawLine(first.x , first.y, secnd.x, secnd.y, 1);

				first = secnd;
				
			}
			m_2dRenderer->setRenderColour(1, 0, 0);
			m_2dRenderer->drawCircle(vecs[0].x, vecs[0].y, 2);
			m_2dRenderer->setRenderColour(0, 1, 0);
			m_2dRenderer->drawCircle(vecs[1].x, vecs[1].y, 2);
			m_2dRenderer->setRenderColour(0, 0, 1);
			m_2dRenderer->drawCircle(vecs[2].x, vecs[2].y, 2);
			
			

			vecs.clear();
			auto temp = reflection_sphere + intersect_point_sphere;
			m_2dRenderer->drawLine((intersect_point_sphere.x), (intersect_point_sphere.y), temp.x, temp.y);
		

		}
	}
	// get point on plane closest to window center 
	auto u = m_plane.closestPoint(Vector2(640,360));
	m_2dRenderer->setRenderColour(1, 0, 1);
	
	// draw plane normal 50 pixels long 
	m_2dRenderer->setRenderColour(1, 0, 0); 
	m_2dRenderer->drawLine(u.x, u.y, u.x + m_plane.N.x * 50, u.y + m_plane.N.y * 50, 4);

	// get a vector perpendicular to the normal 
	Vector2 v(m_plane.N.y, -m_plane.N.x);

	// draw separating line 3000 pixels long 
	m_2dRenderer->setRenderColour(1, 1, 0); 
	m_2dRenderer->drawLine(u.x - v.x * 1500, u.y - v.y * 1500, u.x + v.x * 1500, u.y + v.y * 1500, 4);
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

