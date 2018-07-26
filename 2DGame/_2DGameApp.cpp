#include "_2DGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

_2DGameApp::_2DGameApp() : m_isGameOver(false), m_currentPlayer(1) {

}

_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_croissant = new aie::Texture("../bin/textures/croissant.png");
	m_cupcake = new aie::Texture("../bin/textures/cake.png");

	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			m_board[i][j] = 0;
		}
	}

	return true;
}

void _2DGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_croissant;
	delete m_cupcake;
}

bool _2DGameApp::checkForWin()
{
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			int temp = m_board[j][i]; // either 1 or 2 or 0
			if (temp == 0)
			{
				return false;
			}
			if ((temp == m_board[j + 1][i]) && (m_board[j][i] == m_board[j + 2][i]) && (m_board[j][i] == m_board[j + 3][i]))
			{
				return true;
			}
			if ((temp == m_board[j - 1][i]) && (temp == m_board[j - 2][i]) && (temp == m_board[j - 3][i]))
			{
				return true;
			}
			if ((temp == m_board[j ][i + 1]) && ( temp == m_board[j][i + 2])&&(temp == m_board[j][i + 3]))
			{
				return true;
			}
			if ((temp == m_board[j][i - 1])&&(temp == m_board[j][i - 2])&&(temp == m_board[j][i - 3]))
			{
				return true;
			}
			if ((temp == m_board[j + 1][i + 1])&&(temp == m_board[j + 1][i + 2])&&(temp == m_board[j + 1][i + 3]))
			{
				return true;
			}
			if ((temp  == m_board[j - 1][i - 1] )&&(temp == m_board[j - 1][i - 2] )&&(temp== m_board[j - 1][i - 3]))
			{
				return true;
			}
			if ((temp == m_board[j + 1][i - 1])&&( temp == m_board[j + 1][i - 2])&&( temp == m_board[j + 1][i - 3]))
			{
				return true;
			}
			if ((temp == m_board[j - 1][i + 1])&&( temp == m_board[j - 1][i + 2])&&( temp == m_board[j - 1][i + 3]))
			{
				return true;
			}
		}
	}
	return false;
	/*For each tile on the x axis
	For each tile on the y axis
	Get the tile at location x, y

	If the tile is empty, continue to the next tile
	If the next 3 tiles to the right match the current
	tile, return true
	If the previous 3 tiles to the left match the current
	tile, return true
	If the 3 tiles above the current tile match the
	current tile, return true
	If the 3 tiles below the current tile match the
	current tile, return true
	If the 3 tiles diagonally to the right and down match
	the current tile, return true
	If the 3 tiles diagonally to the left and down match
	the current tile, return true
	If the 3 tiles diagonally to the right and up match
	the current tile, return true
	If the 3 tiles diagonally to the left and up match
	the current tile, return true
	return false*/
}

void _2DGameApp::update(float deltaTime) {
	static int height = this->getWindowHeight();
	static int width = this->getWindowWidth();
	static bool wasMouseDown = false;

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (!m_isGameOver) {
		if (input->isMouseButtonDown(0) && wasMouseDown == false)
		{
			int x = 0, y = 0;
			input->getMouseXY(&x, &y);

			float xInc = (width - (BORDER << 1)) / COLUMNS;
			int col = (x - BORDER) / xInc;

			if (col >= 0 && col < COLUMNS) {
				// find the lowest row and place a tile there
				for (int row = 0; row < ROWS; row++)
				{
					if (m_board[col][row] == 0) {
						m_board[col][row] = m_currentPlayer;

						m_currentPlayer = (m_currentPlayer == 1) ? 2 : 1;

						break;
					}
				}
			}
		}
		wasMouseDown = input->isMouseButtonDown(0);

		m_isGameOver = checkForWin();
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _2DGameApp::draw() {
	static int height = this->getWindowHeight();
	static int width = this->getWindowWidth();

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw game board
	float xInc = (width - (BORDER << 1)) / COLUMNS;
	float yInc = (height - (BORDER << 1)) / ROWS;
	for (int x = 0; x <= COLUMNS; x++) {
		m_2dRenderer->drawLine(BORDER + x*xInc, BORDER + yInc*ROWS, BORDER + x*xInc, BORDER);
	}
	for (int y = 0; y <= ROWS; y++) {
		m_2dRenderer->drawLine(BORDER, BORDER + y*yInc, BORDER + xInc*COLUMNS, BORDER + y*yInc);
	}

	for (int i = 0; i < COLUMNS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (m_board[i][j] == 1) {
				m_2dRenderer->drawSprite(m_croissant, 50 + i*xInc, 50 + j*yInc, xInc, yInc, 0, 0, 0, 0);
			}
			else if (m_board[i][j] == 2) {
				m_2dRenderer->drawSprite(m_cupcake, 50 + i*xInc, 50 + j*yInc, xInc, yInc, 0, 0, 0, 0);
			}
		}
	}

	if (m_isGameOver) {
		m_2dRenderer->setRenderColour(1, 0, 0);
		m_2dRenderer->drawText(m_font, "GAME OVER", (width >> 1) - 50, height - 30);
	}
	else {
		if (m_currentPlayer == 1) {
			m_2dRenderer->setRenderColour(0, 1, 0);
			m_2dRenderer->drawText(m_font, "Player 1 go", 10, height - 30);
		}
		else {
			m_2dRenderer->setRenderColour(1, 0, 0);
			m_2dRenderer->drawText(m_font, "Player 2 go", 10, height - 30);
		}
	}

	m_2dRenderer->setRenderColour(1, 1, 1);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}