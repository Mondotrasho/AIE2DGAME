#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Ray.h"
#include "GrapplePoint.h"
#include "Worm.h"
#include "LevelManager.h"


class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();

	virtual bool startup();
	virtual void shutdown();

	
	virtual void update(float deltaTime);
	virtual void draw();

protected:
	//App stuff
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*	m_font;//FPS FONT
	float m_timer;//DELTA TIME MEMBER VAR

	//GrapplePoint stuff
	std::vector<GrapplePoint> box;

	//player stuff
	Grapple player;
	std::vector<Vector2> vecs;

	//worm stuff
	std::vector<Worm> worm_box;
	float m_timer2;//worm timer

	//level stuff
	LevelManager level;
	Plane Ground, Roof, Right, Left;
	std::vector<Plane> walls;
};
