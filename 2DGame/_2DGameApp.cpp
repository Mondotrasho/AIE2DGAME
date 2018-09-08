#include "_2DGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"


_2DGameApp::_2DGameApp() {

}

_2DGameApp::~_2DGameApp() {

}
aie::Font* g_systemFont = nullptr;
bool _2DGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	g_systemFont = new aie::Font("../bin/font/consolas.ttf", 32);

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_timer = 0;

	m_binaryTree.insert(10);
	m_binaryTree.insert(5);
	m_binaryTree.insert(7);
	m_binaryTree.insert(15);
	m_binaryTree.insert(17);
	m_binaryTree.insert(12);
	m_binaryTree.insert(14);
		
	//m_binaryTree.remove(m_binaryTree.Root(), 10);
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

	static int value = 0;
	ImGui::InputInt("Value", &value);
	if (ImGui::Button("Insert", ImVec2(50, 0)))
	{
		m_binaryTree.insert(value);
		m_selectedNode = m_binaryTree.find(value);
	}
	if (ImGui::Button("Remove", ImVec2(50, 0)))
	{
		m_binaryTree.remove(m_binaryTree.Root(), value);
	}
	if (ImGui::Button("Find", ImVec2(50, 0)))
	{
		m_selectedNode = m_binaryTree.find(value);
	}



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
	m_binaryTree.draw(m_2dRenderer, m_selectedNode);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}