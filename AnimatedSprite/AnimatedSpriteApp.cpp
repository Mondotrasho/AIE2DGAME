#include "AnimatedSpriteApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

AnimatedSpriteApp::AnimatedSpriteApp() {

}

AnimatedSpriteApp::~AnimatedSpriteApp() {

}

bool AnimatedSpriteApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	std::shared_ptr<aie::Texture> frame1 = std::make_shared<aie::Texture>("../bin/textures/alienGreen_walk1.png");
	std::shared_ptr<aie::Texture> frame2 = std::make_shared<aie::Texture>("../bin/textures/alienGreen_walk2.png");

	m_sprite.addFrame(frame1, 0.3f);
	m_sprite.addFrame(frame2, 0.3f);

	m_sprite2.addFrame(frame1, 0.3f);
	m_sprite2.addFrame(frame2, 0.3f);

	m_sprite3.addFrame(frame1, 0.3f);
	m_sprite3.addFrame(frame2, 0.3f);

	m_position.x =  200;
	m_position.y = getWindowHeight() >> 1;

	m_position2.x = 400;
	m_position2.y = getWindowHeight() >> 1;
	m_position3.x = 600;
	m_position3.y = getWindowHeight() >> 1;
	return true;
}

void AnimatedSpriteApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void AnimatedSpriteApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_sprite.update(deltaTime);
	m_sprite2.update(deltaTime);
	m_sprite3.update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void AnimatedSpriteApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_sprite.draw(m_2dRenderer, m_position.x, m_position.y, 0);// DRAW_FLIP_X | DRAW_FLIP_Y);
	m_sprite2.draw(m_2dRenderer, m_position2.x, m_position2.y, 0);// DRAW_FLIP_X | DRAW_FLIP_Y);
	m_sprite3.draw(m_2dRenderer, m_position3.x, m_position3.y, 0);//DRAW_FLIP_X | DRAW_FLIP_Y);
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}