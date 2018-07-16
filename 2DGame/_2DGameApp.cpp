#include "_2DGameApp.h"

_2DGameApp::_2DGameApp() {

}

_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_timer = 0;
	//Initialize yo shite
	return true;
}

void _2DGameApp::shutdown() {

	//delete yo shite
	delete m_2dRenderer;
}

void _2DGameApp::update(float deltaTime) {
	m_timer += deltaTime;


	//do yo shite

	// exit the application
	if (0)
		quit();
}

void _2DGameApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	
	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your shit here!
	//VVVVVV

	//^^^^^^
	// done drawing shit
	m_2dRenderer->end();
}