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
	Layout layout = Layout(layout_pointy,Point(20,20),Point(getWindowWidth()/2,getWindowHeight()/2));

	std::vector<Hex> hexes;
	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 6; ++i)
		{
			hexes.push_back(hex->hex_neighbor(hex->hex_add(*hex,Hex(j-10,0, -j-10)), i));
		}		
	}
	std::vector<std::vector<Point>> list;
	for (auto aHex : hexes)
	{
		list.push_back(aHex.polygon_corners(layout, aHex));
	}

	

	//green
	m_2dRenderer->setRenderColour(0, 1, 0);
	for (auto point : list)
	{
		for (auto coords : point)
		{
			m_2dRenderer->drawCircle(coords.x, coords.y, 3);
		}
	}
	
	//red
	m_2dRenderer->setRenderColour(1, 0, 0);
	for (auto point : list)
	{
		
			m_2dRenderer->drawLine(point[0].x, point[0].y, point[1].x, point[1].y, 1);
			m_2dRenderer->drawLine(point[1].x, point[1].y, point[2].x, point[2].y, 1);
			m_2dRenderer->drawLine(point[2].x, point[2].y, point[3].x, point[3].y, 1);
			m_2dRenderer->drawLine(point[3].x, point[3].y, point[4].x, point[4].y, 1);
			m_2dRenderer->drawLine(point[4].x, point[4].y, point[5].x, point[5].y, 1);
			m_2dRenderer->drawLine(point[5].x, point[5].y, point[0].x, point[0].y, 1);
		
	}


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