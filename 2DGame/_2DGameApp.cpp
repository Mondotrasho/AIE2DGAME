#include "_2DGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Vector2.h"


_2DGameApp::_2DGameApp() {

}

_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {

	m_2dRenderer = new aie::Renderer2D();
	//640,360
	m_plane = Plane(Vector2(620, 340), Vector2(680, 400));
		// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_timer = 0;

	

	return true;
}

void _2DGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void _2DGameApp::update(float deltaTime) {

	m_timer += deltaTime;

	
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

	//....

	Vector2 perp = { -m_plane.N.y,m_plane.N.x };
	Vector2 p1 = m_plane.N * -m_plane.d + perp * 1000;
	Vector2 p2 = m_plane.N * -m_plane.d - perp * 1000;
	
	m_2dRenderer->drawLine(p1.x,p1.y,p2.x,p2.y, 1);
	// get point on plane closest to window center 
	Vector2 u = m_plane.closestPoint({ 800,360 });

	m_2dRenderer->drawLine(800, 360, u.x, u.y);

	//m_2dRenderer->drawLine(620, 340, 680, 400);
	//// draw plane normal 50 pixels long 
	//m_2dRenderer->setRenderColour(1, 0, 0); 
	//m_2dRenderer->drawLine(u.x, u.y, u.x + m_plane.N.x * 50, u.y + m_plane.N.y * 50, 4);
	//// draws a simple coloured line with a given thickness
	//// depth is in the range [0,100] with lower being closer to the viewer
	//
	////virtual void drawLine(float x1, float y1, float x2, float y2, float thickness = 1.0f, float depth = 0.0f);
	//// get a vector perpendicular to the normal 
	//Vector2 v(m_plane.N.y, -m_plane.N.x);
	//// draw separating line 3000 pixels long 
	//m_2dRenderer->setRenderColour(1, 1, 0); 
	//m_2dRenderer->drawLine(u.x - v.x * 1500, u.y - v.x * 1500, u.x + v.x * 1500, u.y + v.y * 1500, 4);



	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}