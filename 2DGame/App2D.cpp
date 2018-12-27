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
	
	//Grid layout orientation then size and position
	GridLayout = new Layout(layout_pointy, Point(20, 20), Point(getWindowWidth() / 2, getWindowHeight() / 2));

	//fill hex grid vector using the Q or HEIGHT and the R or WIDTH to generate
	for (auto k = -GridHeight /2; k <  GridHeight / 2; ++k)
	{
		for (auto j = -GridWidth / 2; j < GridWidth / 2; ++j)
		{
			HexGrid->push_back(HexCenter->hex_neighbor(Hex::hex_add(*HexCenter, Hex(j - k, k)), HexDirection));
		}
	}
	//find the corners of all the hexes we created for the grid
	for (const auto& a_hex : *HexGrid)
	{
		HexGridCorners->push_back(a_hex.polygon_corners(*GridLayout, a_hex));
	}

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
			keyboardpos.x += 1;
			pausing = true;
			pauseTimer = 0.1f;
		}
		if (input->isKeyDown(aie::INPUT_KEY_KP_1))
		{
			keyboardpos.x += -1;
			pausing = true;
			pauseTimer = 0.1f;
		}
		if (input->isKeyDown(aie::INPUT_KEY_KP_5))
		{
			keyboardpos.y += 1;
			pausing = true;
			pauseTimer = 0.1f;
		}
		if (input->isKeyDown(aie::INPUT_KEY_KP_2))
		{
			keyboardpos.y += -1;
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
	//set the keyboard pos to be the 

	*KeyboardHexCorners = Hex(keyboardpos.x, keyboardpos.y).polygon_corners(*GridLayout, Hex(keyboardpos.x, keyboardpos.y));


	//mouse driven hex updates
	//retrieve mouse coords
	input->getMouseXY(MouseXGetter, MouseYGetter);
	mousepos = Vector2(*MouseXGetter, *MouseYGetter);

	//find the fractional position of the hex
	*MouseHex = Hex::pixel_to_hex(*GridLayout, Point(mousepos.x, mousepos.y));

	if (MouseHex->q > 0)
	{
		MouseHex->q += 0.49f;
	}
	else
	{
		MouseHex->q -= 0.49f;
	}
	if (MouseHex->r > 0)
	{
		MouseHex->r += 0.49f;
	}
	else
	{
		MouseHex->r -= 0.49f;
		
	}


	//find corners of the hex it is in
	*MouseHexCorners = Hex(MouseHex->q, MouseHex->r).polygon_corners(*GridLayout, Hex(MouseHex->q, MouseHex->r));


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
	for (auto point : *HexGridCorners)
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
	m_2dRenderer->drawLine(KeyboardHexCorners->operator[](0).x, KeyboardHexCorners->operator[](0).y, KeyboardHexCorners->operator[](1).x, KeyboardHexCorners->operator[](1).y, 1);
	m_2dRenderer->drawLine(KeyboardHexCorners->operator[](1).x, KeyboardHexCorners->operator[](1).y, KeyboardHexCorners->operator[](2).x, KeyboardHexCorners->operator[](2).y, 1);
	m_2dRenderer->drawLine(KeyboardHexCorners->operator[](2).x, KeyboardHexCorners->operator[](2).y, KeyboardHexCorners->operator[](3).x, KeyboardHexCorners->operator[](3).y, 1);
	m_2dRenderer->drawLine(KeyboardHexCorners->operator[](3).x, KeyboardHexCorners->operator[](3).y, KeyboardHexCorners->operator[](4).x, KeyboardHexCorners->operator[](4).y, 1);
	m_2dRenderer->drawLine(KeyboardHexCorners->operator[](4).x, KeyboardHexCorners->operator[](4).y, KeyboardHexCorners->operator[](5).x, KeyboardHexCorners->operator[](5).y, 1);
	m_2dRenderer->drawLine(KeyboardHexCorners->operator[](5).x, KeyboardHexCorners->operator[](5).y, KeyboardHexCorners->operator[](0).x, KeyboardHexCorners->operator[](0).y, 1);

	//change colour to Red
	m_2dRenderer->setRenderColour(1, 0, 0);	
	
	//draw the mouse hex
	m_2dRenderer->drawLine(MouseHexCorners->operator[](0).x, MouseHexCorners->operator[](0).y, MouseHexCorners->operator[](1).x, MouseHexCorners->operator[](1).y, 1);
	m_2dRenderer->drawLine(MouseHexCorners->operator[](1).x, MouseHexCorners->operator[](1).y, MouseHexCorners->operator[](2).x, MouseHexCorners->operator[](2).y, 1);
	m_2dRenderer->drawLine(MouseHexCorners->operator[](2).x, MouseHexCorners->operator[](2).y, MouseHexCorners->operator[](3).x, MouseHexCorners->operator[](3).y, 1);
	m_2dRenderer->drawLine(MouseHexCorners->operator[](3).x, MouseHexCorners->operator[](3).y, MouseHexCorners->operator[](4).x, MouseHexCorners->operator[](4).y, 1);
	m_2dRenderer->drawLine(MouseHexCorners->operator[](4).x, MouseHexCorners->operator[](4).y, MouseHexCorners->operator[](5).x, MouseHexCorners->operator[](5).y, 1);
	m_2dRenderer->drawLine(MouseHexCorners->operator[](5).x, MouseHexCorners->operator[](5).y, MouseHexCorners->operator[](0).x, MouseHexCorners->operator[](0).y, 1);
	
	//draw text
	//fractional point of mouse pos
	m_2dRenderer->drawText(m_font, ("Q   : " + std::to_string(MouseHex->q)).c_str(), 0, 520 - 64);
	m_2dRenderer->drawText(m_font, ("Q + : " + std::to_string(MouseHex->q + 0.49f)).c_str(), 0, 495 - 64);
	m_2dRenderer->drawText(m_font, ("Q - : " + std::to_string(MouseHex->q - 0.49f)).c_str(), 0, 470 - 64);
	m_2dRenderer->drawText(m_font, ("R   : " + std::to_string(MouseHex->r)).c_str(), 0, 420 - 64);
	m_2dRenderer->drawText(m_font, ("R + : " + std::to_string(MouseHex->r + 0.49f)).c_str(), 0, 395 - 64);
	m_2dRenderer->drawText(m_font, ("R - : " + std::to_string(MouseHex->r - 0.49f)).c_str(), 0, 370 - 64);
	m_2dRenderer->drawText(m_font, ("S   : " + std::to_string(MouseHex->s)).c_str(), 0, 320 - 64);
	m_2dRenderer->drawText(m_font, ("S + : " + std::to_string(MouseHex->s + 0.49f)).c_str(), 0, 295 - 64);
	m_2dRenderer->drawText(m_font, ("S - : " + std::to_string(MouseHex->s - 0.49f)).c_str(), 0, 270 - 64);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}