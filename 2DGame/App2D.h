#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "DotAgent.h"

#include "VelocityAgent.h"
#include "SteeringBehaviour.h"
#include "FlowForce.h"


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

	float m_cameraX, m_cameraY;
	float m_timer;

	SteeringBehaviour follow;
	Agent* mouse;
	Agent* m_gameObjects[40];
	FlowForce* flowforce;

	enum eFlowFieldCosts : unsigned short {
		WALKABLE = 1,
		IMPASSABLE = 0xffff,
	};

	enum eFlowFieldSize {
		FLOWFIELD_ROWS = 23,
		FLOWFIELD_COLS = 40,
		FLOWFIELD_CELLSIZE = 32,
	};

	// contains movement costs through the field
	unsigned short	m_costField[FLOWFIELD_ROWS][FLOWFIELD_COLS];

	// contains actual travel cost to goal cell
	float			m_integrationField[FLOWFIELD_ROWS][FLOWFIELD_COLS];

	// the vector flow field that travels towards the goal cell
	Vector2			m_flowField[FLOWFIELD_ROWS][FLOWFIELD_COLS];

	// percentage of grid taken up by obstacles
	float m_obstaclePercentage = 0.05f;

	// randomly generates obstacles and places entities safely
	void randomiseLevel(float obstaclePercentage);

	// the neighbours parameter will be filled with 2x int for 
	// every neighbour ([y][x] within the field)
	// ignores impassable neighbours
	void getCellNeighbours(int x, int y, std::vector<int>& neighbours);

	// generate dijkstras to goal cell
	void performIntergration(int goalX, int goalY);

	// calculate flow based on gScores
	void generateFlowfield();

};
