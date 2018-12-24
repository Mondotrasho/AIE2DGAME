#include "App2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

App2D::App2D() {

}

App2D::~App2D() {

}

bool App2D::startup() {
	//Hex system
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	hex = new Hex{ 0,0,0 };
	otherhex = new Hex(2, 0, -2);

	mode = 0;

	return true;
}

void App2D::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void App2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(aie::INPUT_KEY_KP_1)) { mode = 0; }
	if (input->isKeyDown(aie::INPUT_KEY_KP_2)) { mode = 1; }
	if (input->isKeyDown(aie::INPUT_KEY_KP_3)) { mode = 2; }
	if (input->isKeyDown(aie::INPUT_KEY_KP_4)) { mode = 3; }
	if (input->isKeyDown(aie::INPUT_KEY_KP_5)) { mode = 4; }
	if (input->isKeyDown(aie::INPUT_KEY_KP_6)) { mode = 5; }
	
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void App2D::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);
	// begin drawing sprites
	m_2dRenderer->begin();

	

	// draw your stuff here!
	Layout layout = Layout(layout_flat,Point(20,20),Point(getWindowWidth()/2,getWindowHeight()/2));
	
	//blue
	m_2dRenderer->setRenderColour(0, 0, 1);



	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}