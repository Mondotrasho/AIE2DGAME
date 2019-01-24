#pragma once
#include "Hex.h"
#include "HexSprite.h"

class App2D;

class DebugFunctions
{
public:
	DebugFunctions();
	DebugFunctions(bool grid, bool keys, bool mouse, bool drawgrid, bool drawline, bool drawdots, bool drawSprites);
	~DebugFunctions();

	void startup(App2D* app);
	void update(float deltaTime);
	void draw(aie::Renderer2D* render);

	bool 
			KeyboardControls,
			MouseControls,
			DrawGrid,
			DrawlineToTarget,
			DrawHexDots,
			DrawSpritesOnGrid,
			Grid 
								= false;


	aie::Font*			debugfont;

	//grid layout
	//"pointy" or "flat" also controls starting position and the hex size for anything it is used with
	Layout* GridLayout;
	Point* HalfWindow;
	//used to draw from grid is created from this point
	Hex* HexCenter = new Hex(0, 0, 0);
	//the direction from a hex [0-5] in this case it decides which way from the center hex the grid is drawn
	int HexDirection = 0;

	//KeyboardControls
	//using num pad to move a hex using the axial position on a hex
	std::vector<Point>* KeyboardHexCorners = new std::vector<Point>();
	Vector2 keyboardpos = Vector2(0, 0);
	//pause for input control
	bool pausing = false;
	float pauseTimer = 0;

	//hexGrid
	//the "map" atm all code uses thisin its current form to lay things out code creates a "board" that everything else is placed on
	int GridHeight = 5;
	int GridWidth = 10;
	std::vector<Hex>* HexGrid = new std::vector<Hex>();
	std::vector<std::vector<Point>>* HexGridCorners = new std::vector<std::vector<Point>>();

	//DrawSprite on grid
	//this shows loading sprites ONTO the hex grid atm it has a standard scale and only works with the dafualt grid (all changes to grid scale need to be reflected in the sprite code)
	std::vector<HexSprite> Sprite_box;
	std::vector<HexSprite>* Sprite_box_ptr;
	int num[100000];

	//MouseControls
	//Moust input to hex location using fractional hex to pixel conversion and rounding to HEX for final position storing
	int* MouseXGetter = new int();
	int* MouseYGetter = new int();
	Hex* LineTarget = new Hex(0, 0, 0);
	Vector2 mousepos = Vector2(0, 0);
	//corners of various specific hexes
	std::vector<Point>* MouseHexCorners = new std::vector<Point>();
	//the fractional hex representing mouse position
	FractionalHex* MouseHex = new FractionalHex(0, 0, 0);

};

