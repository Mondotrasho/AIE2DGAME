#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "App2D.h"
#include <list>
#include "imgui.h"
#include "FollowBehaviour.h"

App2D::App2D() {

}

App2D::~App2D() {

}

bool App2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_navMesh = new NavMesh(1280, 720);

	// just to help mess with the random
	srand(42);

	// random obstacles
	for (int i = 0; i < 12; ++i) {

		bool safe = false;
		do {
			safe = m_navMesh->addObstacle(rand() / float(RAND_MAX) * getWindowWidth() * 0.75f + getWindowWidth() * 0.125f,
				rand() / float(RAND_MAX) * getWindowHeight() * 0.75f + getWindowHeight() * 0.125f,
				60, 60,
				10);
		} while (safe == false);
	}

	m_navMesh->build();

	return true;
}

void App2D::shutdown() {

	delete m_navMesh;

	delete m_font;
	delete m_2dRenderer;
}

void App2D::update(float deltaTime) {
	

	// input example
	aie::Input* input = aie::Input::getInstance();
	//mouse->set_position(Vector2(input->getMouseX(), input->getMouseY()));
	//thing->update(deltaTime);
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void App2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	// draw nav mesh polygons
	for (auto node : m_navMesh->getNodes()) {

		m_2dRenderer->setRenderColour(1, 1, 0);
		m_2dRenderer->drawLine(node->vertices[0].x, node->vertices[0].y, node->vertices[1].x, node->vertices[1].y);
		m_2dRenderer->drawLine(node->vertices[1].x, node->vertices[1].y, node->vertices[2].x, node->vertices[2].y);
		m_2dRenderer->drawLine(node->vertices[2].x, node->vertices[2].y, node->vertices[0].x, node->vertices[0].y);
	}

	// draw obstacles
	m_2dRenderer->setRenderColour(1, 0, 0);
	for (auto& o : m_navMesh->getObstacles()) {
		m_2dRenderer->drawBox(o.x + o.w * 0.5f, o.y + o.h * 0.5f, o.w, o.h);
	}
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);
	//m_2dRenderer->drawText(m_font,("delta   : " + (std::to_string(mouse->pos.x))).c_str() 
	//	, 100, getWindowWidth() / 2 + 100);

	// done drawing sprites
	m_2dRenderer->end();
}
