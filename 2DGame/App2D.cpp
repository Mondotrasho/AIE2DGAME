#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "App2D.h"
#include <list>
#include "imgui.h"

App2D::App2D() {

}

App2D::~App2D() {

}

bool App2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);
	return true;
}

void App2D::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void App2D::update(float deltaTime) {
	//mouse->set_position(Vector2(ImGui::GetMousePos().x, ImGui::GetMousePos().y));

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void App2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// done drawing sprites
	m_2dRenderer->end();
}
