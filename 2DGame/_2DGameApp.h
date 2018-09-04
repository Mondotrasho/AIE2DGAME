#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Ray.h"
#include "Vector3.h"
#include "GrapplePoint.h"
#include "Worm.h"


class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();

	virtual bool startup();
	virtual void shutdown();

	
	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;


	aie::Font*	m_font;//FPS FONT
	float m_timer;//DELTA TIME MEMBER VAR

	float m_rayAngle;
	Ray m_ray;
	Vector2 m_point;

	std::vector<GrapplePoint> box;
	Grapple test = { Vector2(-1000,-1000),Vector2(-1000,-1000) };
	Grapple player;
	Plane Ground,Roof,Right,Left;
	std::vector<Plane> walls;
	std::vector<Vector2> vecs;

	//colours
	Vector3 m_colour;
	Worm w1, w2, w3, w4,w5,w6,w7,w8,w9,w10;
	std::vector<Worm> worm_box;
	float m_timer2;//worm timer
};
