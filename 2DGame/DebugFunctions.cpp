#include "DebugFunctions.h"
#include "Input.h"
#include "Font.h"
#include "App2D.h"


DebugFunctions::DebugFunctions()
{
}

DebugFunctions::DebugFunctions(bool grid,bool keys,bool mouse , bool drawgrid,bool drawline,bool drawdots,bool drawSprites)
{
	Grid = grid;
	KeyboardControls = keys;
	MouseControls = mouse;
	DrawGrid = drawgrid;
	DrawlineToTarget = drawline;
	DrawHexDots = drawdots;
	DrawSpritesOnGrid = drawSprites;

}


DebugFunctions::~DebugFunctions()
{
}


void DebugFunctions::startup(App2D* app)
{
	debugfont = new aie::Font("../bin/font/consolas.ttf", 32);
	if (Grid) {
		HalfWindow = new Point(app->getWindowWidth() / 2, app->getWindowHeight() / 2);


		//Grid layout orientation then size and position
		GridLayout = new Layout(layout_pointy, Point(30 / 2, 30 / 2), *HalfWindow);

		//fill hex grid vector using the Q or HEIGHT and the R or WIDTH to generate
		for (auto k = -GridHeight / 2; k < GridHeight / 2; ++k)
		{
			for (auto j = -GridWidth / 2; j < GridWidth / 2; ++j)
			{
				HexGrid->push_back(HexCenter->hex_neighbor(Hex::hex_add(*HexCenter, Hex(j - k, k)), HexDirection));
			}
		}
	}

	if (KeyboardControls)
	{

	}
	if (MouseControls)
	{

	}
	if (DrawGrid)
	{
		//find the corners of all the hexes we created for the grid
		for (const auto& a_hex : *HexGrid)
		{
			HexGridCorners->push_back(a_hex.polygon_corners(*GridLayout, a_hex));
		}
	}
	if (DrawlineToTarget)
	{

	}
	if (DrawHexDots)
	{

	}
	if (DrawSpritesOnGrid)
	{
		Sprite_box.push_back(HexSprite());
		Sprite_box.back().setup("../bin/textures/Tile2P.png");
		Sprite_box.back().setPosition(HalfWindow->x, HalfWindow->y);
		Sprite_box.back().Hex_states = 0;
		Sprite_box.back().done = true;

		Sprite_box_ptr = new std::vector<HexSprite>;

		Sprite_box_ptr->push_back(HexSprite());
		Sprite_box_ptr->back().setup("../bin/textures/Tile1P.png");
		Sprite_box_ptr->back().setPosition(HalfWindow->x, HalfWindow->y);
		Sprite_box_ptr->back().Hex_states = 0;
		Sprite_box_ptr->back().done = true;

		for (int i = 0; i < 10; ++i)
		{
			Sprite_box_ptr->push_back(HexSprite());
			Sprite_box_ptr->back().setup("../bin/textures/Tile2P.png");
			Sprite_box_ptr->back().setPosition(HalfWindow->x, HalfWindow->y);
			Sprite_box_ptr->back().Hex_states = 0;
			Sprite_box_ptr->back().done = true;


		}

		//records the tile ID s atm
		Sprite_box_ptr->resize(10000);
		for (int i = 0; i < 10000; ++i)
		{

			num[i] = rand() % 10;
		}
	}

}

void DebugFunctions::update(float deltaTime)
{


	if (KeyboardControls)

	{// input example
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
			if (pauseTimer <= 0)
			{
				pausing = false;
			}
		}
		//set the keyboard pos to be the 

		*KeyboardHexCorners = Hex(keyboardpos.x, keyboardpos.y).polygon_corners(*GridLayout, Hex(keyboardpos.x, keyboardpos.y));
	}
	if (MouseControls)
	{
		// input example
		aie::Input* input = aie::Input::getInstance();
		//mouse driven hex updates
		//retrieve mouse coords
		input->getMouseXY(MouseXGetter, MouseYGetter);
		mousepos = Vector2(*MouseXGetter, *MouseYGetter);

		//find the fractional position of the hex
		*MouseHex = Hex::pixel_to_hex(*GridLayout, Point(mousepos.x, mousepos.y));


		auto test = LineTarget->hex_round(*MouseHex);
		LineTarget = new Hex(test);

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
		if (MouseHex->s > 0)
		{
			MouseHex->s += 0.49f;
		}
		else
		{
			MouseHex->s -= 0.49f;

		}


		//find corners of the hex it is in
		*MouseHexCorners = Hex(MouseHex->q, MouseHex->r).polygon_corners(*GridLayout, Hex(MouseHex->q, MouseHex->r));

	}
	if (DrawGrid)
	{

	}
	if (DrawlineToTarget)
	{

	}
	if (DrawHexDots)
	{

	}
	if (DrawSpritesOnGrid)
	{

	}
}

void DebugFunctions::draw(aie::Renderer2D* render)
{
	if (Grid)
	{
		std::vector<Vector2> gridpoints;
		for (auto thing : *HexGrid)
		{
			Point temppoint = thing.hex_to_pixel(*GridLayout, thing);
			gridpoints.push_back(Vector2((float)temppoint.x, (float)temppoint.y));
		}
		if (KeyboardControls)
		{
			//draw the keyboard driven Hex	
			render->drawLine(KeyboardHexCorners->operator[](0).x, KeyboardHexCorners->operator[](0).y, KeyboardHexCorners->operator[](1).x, KeyboardHexCorners->operator[](1).y, 1);
			render->drawLine(KeyboardHexCorners->operator[](1).x, KeyboardHexCorners->operator[](1).y, KeyboardHexCorners->operator[](2).x, KeyboardHexCorners->operator[](2).y, 1);
			render->drawLine(KeyboardHexCorners->operator[](2).x, KeyboardHexCorners->operator[](2).y, KeyboardHexCorners->operator[](3).x, KeyboardHexCorners->operator[](3).y, 1);
			render->drawLine(KeyboardHexCorners->operator[](3).x, KeyboardHexCorners->operator[](3).y, KeyboardHexCorners->operator[](4).x, KeyboardHexCorners->operator[](4).y, 1);
			render->drawLine(KeyboardHexCorners->operator[](4).x, KeyboardHexCorners->operator[](4).y, KeyboardHexCorners->operator[](5).x, KeyboardHexCorners->operator[](5).y, 1);
			render->drawLine(KeyboardHexCorners->operator[](5).x, KeyboardHexCorners->operator[](5).y, KeyboardHexCorners->operator[](0).x, KeyboardHexCorners->operator[](0).y, 1);

		}
		if (MouseControls)
		{
			//draw the mouse hex
			render->drawLine(MouseHexCorners->operator[](0).x, MouseHexCorners->operator[](0).y, MouseHexCorners->operator[](1).x, MouseHexCorners->operator[](1).y, 1);
			render->drawLine(MouseHexCorners->operator[](1).x, MouseHexCorners->operator[](1).y, MouseHexCorners->operator[](2).x, MouseHexCorners->operator[](2).y, 1);
			render->drawLine(MouseHexCorners->operator[](2).x, MouseHexCorners->operator[](2).y, MouseHexCorners->operator[](3).x, MouseHexCorners->operator[](3).y, 1);
			render->drawLine(MouseHexCorners->operator[](3).x, MouseHexCorners->operator[](3).y, MouseHexCorners->operator[](4).x, MouseHexCorners->operator[](4).y, 1);
			render->drawLine(MouseHexCorners->operator[](4).x, MouseHexCorners->operator[](4).y, MouseHexCorners->operator[](5).x, MouseHexCorners->operator[](5).y, 1);
			render->drawLine(MouseHexCorners->operator[](5).x, MouseHexCorners->operator[](5).y, MouseHexCorners->operator[](0).x, MouseHexCorners->operator[](0).y, 1);

			//draw text
			//fractional point of mouse pos
			render->drawText(debugfont, ("Q   : " + std::to_string(MouseHex->q)).c_str(), 0, 520 - 64);
			render->drawText(debugfont, ("Q   : " + std::to_string(Hex(MouseHex->q, MouseHex->r, MouseHex->s).q)).c_str(), 0, 495 - 64);
			//m_2dRenderer->drawText(m_font, ("Q - : " + std::to_string(MouseHex->q - 0.49f)).c_str(), 0, 470 - 64);
			render->drawText(debugfont, ("R   : " + std::to_string(MouseHex->r)).c_str(), 0, 420 - 64);
			render->drawText(debugfont, ("R   : " + std::to_string(Hex(MouseHex->q, MouseHex->r, MouseHex->s).r)).c_str(), 0, 395 - 64);
			//m_2dRenderer->drawText(m_font, ("R - : " + std::to_string(MouseHex->r - 0.49f)).c_str(), 0, 370 - 64);
			render->drawText(debugfont, ("S   : " + std::to_string(MouseHex->s)).c_str(), 0, 320 - 64);
			render->drawText(debugfont, ("S   : " + std::to_string(Hex(MouseHex->q, MouseHex->r, MouseHex->s).s)).c_str(), 0, 295 - 64);
			//m_2dRenderer->drawText(m_font, ("S - : " + std::to_string(MouseHex->s - 0.49f)).c_str(), 0, 270 - 64);

		}
		if (DrawGrid)
		{
			//draw the grid of hexes from the list we generated in the startup	
			for (auto point : *HexGridCorners)
			{
				render->drawLine(point[0].x, point[0].y, point[1].x, point[1].y, 1);
				render->drawLine(point[1].x, point[1].y, point[2].x, point[2].y, 1);
				render->drawLine(point[2].x, point[2].y, point[3].x, point[3].y, 1);
				render->drawLine(point[3].x, point[3].y, point[4].x, point[4].y, 1);
				render->drawLine(point[4].x, point[4].y, point[5].x, point[5].y, 1);
				render->drawLine(point[5].x, point[5].y, point[0].x, point[0].y, 1);
			}
		}
		if (DrawHexDots || DrawlineToTarget)
		{

			std::vector<Vector2> points;

			std::vector<Hex> OverlappedHex = HexCenter->hex_linedraw(*HexCenter, *LineTarget);
			for each (auto overlapped in OverlappedHex)
			{
				Point temppoint = overlapped.hex_to_pixel(*GridLayout, overlapped);
				points.push_back(Vector2((float)temppoint.x, (float)temppoint.y));
			}

			if (DrawlineToTarget)
			{
				if (!points.empty())
				{
					render->drawLine(points.front().x, points.front().y, points.back().x, points.back().y, 1);
				}
			}

			if (DrawHexDots)
			{
				for each (auto point in points)
				{
					render->drawCircle(point.x, point.y, 8);
				}
			}
		}
		if (DrawSpritesOnGrid)
		{
			int othernum = 1;
			for each (auto point in gridpoints)
			{
				auto a = (*Sprite_box_ptr)[num[othernum]];

				a.translate(point.x - HalfWindow->x, point.y - HalfWindow->y);

				a.draw(render);
				othernum++;
			}

			//example of specific hex from a hex object
			for each (auto sprite in Sprite_box)
			{
				auto a = LineTarget->hex_to_pixel(*GridLayout, *LineTarget);
				sprite.translate(a.x - HalfWindow->x, a.y - HalfWindow->y);
				sprite.draw(render);
			}
		}
	}
}
