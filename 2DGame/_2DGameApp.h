#pragma once

#include "Application.h"
#include "Renderer2D.h"

const int COLUMNS = 7;
const int ROWS = 6;
const int BORDER = 50;

class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	bool checkForWin();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	int					m_board[COLUMNS][ROWS];
	int					m_currentPlayer;
	bool				m_isGameOver;	// be careful, base class defines m_gameOver (which will close the app)

	aie::Texture*		m_croissant;
	aie::Texture*		m_cupcake;
};