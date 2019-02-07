#include "App2D.h"
#include "Font.h"
#include "Input.h"
#include <unordered_map>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <stdlib.h>
#include <stdlib.h>

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

	debug_ = new DebugFunctions(	
		1,
		1,
		1,
		1,
		1,
		1,
		1
	);
	debug_->startup(this);

	int map_radius = 1;

	std::unordered_set<Hex> map;
	for (int q = -map_radius; q <= map_radius; q++) {
		int r1 = std::max(-map_radius, -q - map_radius);
		int r2 = std::min(map_radius, -q + map_radius);
		for (int r = r1; r <= r2; r++) {
			map.insert(Hex(q, r, -q - r));
		}
	}

	heights = new std::unordered_map<Hex, float>;
	heights->operator[](Hex(1, -2, 3) )= 4.3;

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
	debug_->update(deltaTime);

	
}

void App2D::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);
	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	debug_->draw(m_2dRenderer);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}
