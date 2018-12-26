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
	otherhex = new Hex(0, 0, 0);
	mousehex = new Hex{ 0,0,0 };
	fractionalpoint = new FractionalHex(0,0,0);

	KeyboardDrivenHexPos = new std::vector<Point>;
	MouseDrivenHexPos = new std::vector<Point>;
	mode = 0;
	GridLayout = new Layout(layout_pointy, Point(20, 20), Point(getWindowWidth() / 2, getWindowHeight() / 2));
	list = new std::vector<std::vector<Point>>;
	hexes = new std::vector<Hex>;
	for (int k = -5; k < 5; ++k)
	{


		for (int j = -5; j < 5; ++j)
		{
			for (int i = 0; i < 6; ++i)
			{
				hexes->push_back(otherhex->hex_neighbor(otherhex->hex_add(*otherhex, Hex(j - k, k)), mode));
			}
		}
	}
	for (auto aHex : *hexes)
	{
		list->push_back(aHex.polygon_corners(*GridLayout, aHex));
	}

	active = Vector2(0, 0);
	pausing = false;
	pauseTimer = 0;

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

	//keyboard driven hex updates
	if (!pausing) {
		if (input->isKeyDown(aie::INPUT_KEY_KP_4))
		{
			active.x = 1;
			pausing = true;
			pauseTimer = 0.1f;
		}
		if (input->isKeyDown(aie::INPUT_KEY_KP_1))
		{
			active.x = -1;
			pausing = true;
			pauseTimer = 0.1f;
		}
		if (input->isKeyDown(aie::INPUT_KEY_KP_5))
		{
			active.y = 1;
			pausing = true;
			pauseTimer = 0.1f;
		}
		if (input->isKeyDown(aie::INPUT_KEY_KP_2))
		{
			active.y = -1;
			pausing = true;
			pauseTimer = 0.1f;
		}
	}
	if (pauseTimer > 0)
	{
		pauseTimer -= deltaTime;
		if(pauseTimer <= 0)
		{
			pausing = false;
		}
	}
	hex = new Hex(hex->q + active.x, hex->r + active.y);
	active = Vector2(0, 0);
	*KeyboardDrivenHexPos = hex->polygon_corners(*GridLayout, *hex);

	//mouse driven hex updates
	int* num1 = new int(0);
	int* num2 = new int(0);
	input->getMouseXY(num1, num2);
	mousepos = Vector2(*num1, *num2);
	*fractionalpoint = mousehex->pixel_to_hex(*GridLayout, Point(mousepos.x, mousepos.y));
	*fractionalpoint = FractionalHex(fractionalpoint->q, fractionalpoint->r, fractionalpoint->s);
	mousehex = new Hex(fractionalpoint->q, fractionalpoint->r);
	*MouseDrivenHexPos = mousehex->polygon_corners(*GridLayout, *mousehex);
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

	//change colour to Green
	m_2dRenderer->setRenderColour(0, 1, 0);

	//draw the grid of hexes from the list we generated in the startup	
	for (auto point : *list)
	{
		m_2dRenderer->drawLine(point[0].x, point[0].y, point[1].x, point[1].y, 1);
		m_2dRenderer->drawLine(point[1].x, point[1].y, point[2].x, point[2].y, 1);
		m_2dRenderer->drawLine(point[2].x, point[2].y, point[3].x, point[3].y, 1);
		m_2dRenderer->drawLine(point[3].x, point[3].y, point[4].x, point[4].y, 1);
		m_2dRenderer->drawLine(point[4].x, point[4].y, point[5].x, point[5].y, 1);
		m_2dRenderer->drawLine(point[5].x, point[5].y, point[0].x, point[0].y, 1);
	}

	//change colour to Blue
	m_2dRenderer->setRenderColour(0, 0, 1);

	//draw the keyboard driven Hex	
	m_2dRenderer->drawLine(KeyboardDrivenHexPos->operator[](0).x, KeyboardDrivenHexPos->operator[](0).y, KeyboardDrivenHexPos->operator[](1).x, KeyboardDrivenHexPos->operator[](1).y, 1);
	m_2dRenderer->drawLine(KeyboardDrivenHexPos->operator[](1).x, KeyboardDrivenHexPos->operator[](1).y, KeyboardDrivenHexPos->operator[](2).x, KeyboardDrivenHexPos->operator[](2).y, 1);
	m_2dRenderer->drawLine(KeyboardDrivenHexPos->operator[](2).x, KeyboardDrivenHexPos->operator[](2).y, KeyboardDrivenHexPos->operator[](3).x, KeyboardDrivenHexPos->operator[](3).y, 1);
	m_2dRenderer->drawLine(KeyboardDrivenHexPos->operator[](3).x, KeyboardDrivenHexPos->operator[](3).y, KeyboardDrivenHexPos->operator[](4).x, KeyboardDrivenHexPos->operator[](4).y, 1);
	m_2dRenderer->drawLine(KeyboardDrivenHexPos->operator[](4).x, KeyboardDrivenHexPos->operator[](4).y, KeyboardDrivenHexPos->operator[](5).x, KeyboardDrivenHexPos->operator[](5).y, 1);
	m_2dRenderer->drawLine(KeyboardDrivenHexPos->operator[](5).x, KeyboardDrivenHexPos->operator[](5).y, KeyboardDrivenHexPos->operator[](0).x, KeyboardDrivenHexPos->operator[](0).y, 1);

	//change colour to Red
	m_2dRenderer->setRenderColour(1, 0, 0);	
	
	//draw the mouse hex
	m_2dRenderer->drawLine(MouseDrivenHexPos->operator[](0).x, MouseDrivenHexPos->operator[](0).y, MouseDrivenHexPos->operator[](1).x, MouseDrivenHexPos->operator[](1).y, 1);
	m_2dRenderer->drawLine(MouseDrivenHexPos->operator[](1).x, MouseDrivenHexPos->operator[](1).y, MouseDrivenHexPos->operator[](2).x, MouseDrivenHexPos->operator[](2).y, 1);
	m_2dRenderer->drawLine(MouseDrivenHexPos->operator[](2).x, MouseDrivenHexPos->operator[](2).y, MouseDrivenHexPos->operator[](3).x, MouseDrivenHexPos->operator[](3).y, 1);
	m_2dRenderer->drawLine(MouseDrivenHexPos->operator[](3).x, MouseDrivenHexPos->operator[](3).y, MouseDrivenHexPos->operator[](4).x, MouseDrivenHexPos->operator[](4).y, 1);
	m_2dRenderer->drawLine(MouseDrivenHexPos->operator[](4).x, MouseDrivenHexPos->operator[](4).y, MouseDrivenHexPos->operator[](5).x, MouseDrivenHexPos->operator[](5).y, 1);
	m_2dRenderer->drawLine(MouseDrivenHexPos->operator[](5).x, MouseDrivenHexPos->operator[](5).y, MouseDrivenHexPos->operator[](0).x, MouseDrivenHexPos->operator[](0).y, 1);
	
	//draw text
	//fractional point of mouse pos
	m_2dRenderer->drawText(m_font, ("Q   : " + std::to_string(fractionalpoint->q)).c_str(), 0, 520 - 64);
	m_2dRenderer->drawText(m_font, ("Q + : " + std::to_string(fractionalpoint->q + 0.49f)).c_str(), 0, 495 - 64);
	m_2dRenderer->drawText(m_font, ("Q - : " + std::to_string(fractionalpoint->q - 0.49f)).c_str(), 0, 470 - 64);
	m_2dRenderer->drawText(m_font, ("R   : " + std::to_string(fractionalpoint->r)).c_str(), 0, 420 - 64);
	m_2dRenderer->drawText(m_font, ("R + : " + std::to_string(fractionalpoint->r + 0.49f)).c_str(), 0, 395 - 64);
	m_2dRenderer->drawText(m_font, ("R - : " + std::to_string(fractionalpoint->r - 0.49f)).c_str(), 0, 370 - 64);
	m_2dRenderer->drawText(m_font, ("S   : " + std::to_string(fractionalpoint->s)).c_str(), 0, 320 - 64);
	m_2dRenderer->drawText(m_font, ("S + : " + std::to_string(fractionalpoint->s + 0.49f)).c_str(), 0, 295 - 64);
	m_2dRenderer->drawText(m_font, ("S - : " + std::to_string(fractionalpoint->s - 0.49f)).c_str(), 0, 270 - 64);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}