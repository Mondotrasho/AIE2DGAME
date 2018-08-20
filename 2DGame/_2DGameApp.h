#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Ray.h"
#include "Vector3.h"
#include "GrapplePoint.h"


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
	Grapple test = { Vector2(1,1),Vector2(1,1) };

	Plane m_plane;

	//colours
	Vector3 m_colour;
};
