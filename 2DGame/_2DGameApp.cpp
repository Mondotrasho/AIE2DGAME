#include "_2DGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


_2DGameApp::_2DGameApp() {

}

_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();


	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_timer = 0;

	// load an image
	m_shipTexture = new aie::Texture("../bin/textures/ship.png");
	// position the transform near the center
	m_matrix.z_axis = { getWindowWidth() / 2.f,getWindowHeight() / 2.f,1 };

	return true;
}

void _2DGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void _2DGameApp::update(float deltaTime) {

	m_timer += deltaTime;

	m_matrix.rotate_z(deltaTime);
	
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
	m_2dRenderer->drawSpriteTransformed3x3(m_shipTexture,(float*)&m_matrix);



	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}