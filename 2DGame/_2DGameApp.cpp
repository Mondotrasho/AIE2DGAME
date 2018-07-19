#include "_2DGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <ctime>
#include <random>
#include "_2DGameApp.h"


_2DGameApp::_2DGameApp(): m_2dRenderer(nullptr), m_font(nullptr)
{
}

_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	srand(time(NULL));
	m_snackFactory = std::unique_ptr<SnackFactory>(new SnackFactory());
	// create some snacks to store in the factory
	std::shared_ptr<Snack> cake(new Snack("cake", "../bin/textures/cake.png"));
	cake->setPosition(200, 100);
	std::shared_ptr<Snack> croissant(new Snack("croissant","../bin/textures/croissant.png"));
	croissant->setPosition(500, 400);
	m_snackFactory->addPrototype(cake);
	m_snackFactory->addPrototype(croissant);

	return true;
	
}

void _2DGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void _2DGameApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	static float timer = 0;
	if (timer <= 0) {
		timer = 0.5f;
		std::shared_ptr<IPrototype> snackClone;
		if (rand() % 2 == 0)
			snackClone = m_snackFactory->create("cake");
		else
			snackClone = m_snackFactory->create("croissant");
		// dynamically cast the shared pointer from IPrototype to Snack
		std::shared_ptr<Snack> snack =
			std::dynamic_pointer_cast<Snack>(snackClone);
		snack->setVelocity(50 - rand() % 100, 50 - rand() % 100);
		m_snacks.push_back(snack);
	}
	timer -= deltaTime;
	for (auto it = m_snacks.begin(); it != m_snacks.end(); ) {
		(*it)->update(deltaTime);
		glm::vec2 pos = (*it)->getPosition();
		if (pos.x < 0 || pos.y < 0 || pos.x > this->getWindowWidth() ||
			pos.y > this->getWindowHeight()) {
			it = m_snacks.erase(it);
		}
		else {
			++it;
		}
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
	for (std::shared_ptr<Snack> snack : m_snacks) {
		snack->draw(m_2dRenderer);
	}

	//// output some text, uses the last used colour
	//char fps[32];
	//sprintf_s(fps, 32, "FPS: %i", getFPS());
	//m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	//m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}