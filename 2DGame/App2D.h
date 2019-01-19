#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Hex.h"
#include "HexSprite.h"

class App2D : public aie::Application {
public:

	App2D();
	virtual ~App2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	float m_cameraX = 0;
	float m_cameraY = 0;
	float m_timer = 0;

	//used to draw from grid is created from this point
	Hex* HexCenter = new Hex(0, 0, 0);

	//the fractional hex representing mouse position
	FractionalHex* MouseHex = new FractionalHex(0, 0, 0);

	//the direction from a hex [0-5] in this case it decides which way from the center hex the grid is drawn
	int HexDirection = 0;

	//the "map"
	int GridHeight = 25;
	int GridWidth = 50;
	std::vector<Hex>* HexGrid = new std::vector<Hex>();

	//"pointy" or "flat" also controls starting position and the hex size for anything it is used with
	Layout* GridLayout;

	//corners of various specific hexes
	std::vector<Point>* KeyboardHexCorners = new std::vector<Point>();
	std::vector<Point>* MouseHexCorners = new std::vector<Point>();
	std::vector<std::vector<Point>>* HexGridCorners = new std::vector<std::vector<Point>>();

	//pause for input control
	bool pausing = false;
	float pauseTimer = 0;

	//position of the mouse or the HEX coordinate of the active keyboard controlled point
	Vector2 mousepos = Vector2(0, 0);
	Vector2 keyboardpos = Vector2(0, 0);

	int* MouseXGetter = new int();
	int* MouseYGetter = new int();

	Hex* LineTarget = new Hex(0, 0, 0);

	std::vector<HexSprite> Sprite_box;

};
