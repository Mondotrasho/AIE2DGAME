#include "_2DGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "RayController.h"
#include "PointController.h"
#include "t_controller.h"
#include "Spline.h"

_2DGameApp::_2DGameApp() {

}

_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {

	m_2dRenderer = new aie::Renderer2D();

	//Temp variables for readability
	Vector2 startypoint = { 500, 200 }; // X = 640 Y = 360
	m_point_1 = { 500 , 200 };
	m_point_2 = { 500 , 500 };
	m_point_3 = { 800 , 500 };
	m_point_4 = { 800 , 200 };

	m_colour = { 0.3f,0.7f,0.0f };

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_timer = 0;

	t_value = 1;
	
	

	return true;
}

void _2DGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}



void _2DGameApp::update(float deltaTime) {

	m_timer += deltaTime;
	//0.0 - 1.0
	m_colour.R += deltaTime / 2;
	if (m_colour.R > 1) { m_colour.R = 0; }
	m_colour.G += deltaTime / 2;
	if (m_colour.G > 1) { m_colour.G = 0; }
	m_colour.B += deltaTime / 2;
	if (m_colour.B > 1) { m_colour.B = 0; }
	
	pointcontroller(m_point_1, deltaTime);

	t_controller(t_value , deltaTime);

	spline_point_1 = Spline::lerp_2(m_point_1, m_point_2, t_value);
	spline_point_2 = Spline::lerp_2(m_point_2, m_point_3, t_value);
	spline_point_3 = Spline::lerp_2(m_point_3, m_point_4, t_value);

	mid_point_12 = Spline::lerp_2(spline_point_1 , spline_point_2,t_value);
	mid_point_23 = Spline::lerp_2(spline_point_2, spline_point_3, t_value);

	mid_of_mids = Spline::lerp_2(mid_point_12, mid_point_23, t_value);

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

	// draw your stuff here!
	
	// draw a pink/purle ray
	m_2dRenderer->setRenderColour(m_colour.R, m_colour.G, m_colour.B);

	//place points
	//point IJKL
	m_2dRenderer->drawCircle((m_point_1.x), (m_point_1.y), 10);
	m_2dRenderer->drawCircle((m_point_2.x), (m_point_2.y), 10);
	m_2dRenderer->drawCircle((m_point_3.x), (m_point_3.y), 10);
	m_2dRenderer->drawCircle((m_point_4.x), (m_point_4.y), 10);

	//draw lines between them
	m_2dRenderer->drawLine(m_point_1.x, m_point_1.y, m_point_2.x, m_point_2.y);
	m_2dRenderer->drawLine(m_point_2.x, m_point_2.y, m_point_3.x, m_point_3.y);
	m_2dRenderer->drawLine(m_point_3.x, m_point_3.y, m_point_4.x, m_point_4.y);
	//m_2dRenderer->drawLine(m_point_4.x, m_point_4.y, m_point_1.x, m_point_1.y);

	//draw the t points
	m_2dRenderer->drawCircle((spline_point_1.x), (spline_point_1.y), 10);
	m_2dRenderer->drawCircle((spline_point_2.x), (spline_point_2.y), 10);
	m_2dRenderer->drawCircle((spline_point_3.x), (spline_point_3.y), 10);

	//draw lines connecting the t points
	m_2dRenderer->drawLine(spline_point_1.x, spline_point_1.y, spline_point_2.x, spline_point_2.y);
	m_2dRenderer->drawLine(spline_point_2.x, spline_point_2.y, spline_point_3.x, spline_point_3.y);

	//draw mid points of above lines
	m_2dRenderer->drawCircle(mid_point_12.x, mid_point_12.y, 10);
	m_2dRenderer->drawCircle(mid_point_23.x, mid_point_23.y, 10);
	//draw line between them
	m_2dRenderer->drawLine(mid_point_12.x, mid_point_12.y, mid_point_23.x, mid_point_23.y);

	// last point
	m_2dRenderer->drawCircle(mid_of_mids.x, mid_of_mids.y, 10);

	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

