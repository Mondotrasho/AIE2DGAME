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
	//m_plane = Plane(Vector2(620, 340), Vector2(680, 400));
	m_ray = Ray(Vector2(600, 222), Vector2(399, 300), 10000);
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
	// draw a pink/purle ray
	m_2dRenderer->setRenderColour(1, 0, 1);
	m_2dRenderer->drawCircle(m_ray.origin.x, m_ray.origin.y, 10);
	m_2dRenderer->drawLine(m_ray.origin.x, m_ray.origin.y,
		m_ray.origin.x + m_ray.direction.x *
		m_ray.length,
		m_ray.origin.y + m_ray.direction.y *
		m_ray.length, 5);



	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}