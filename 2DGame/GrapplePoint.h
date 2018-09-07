#pragma once

#include "Grapple.h"
#include "Sphere.h"


class GrapplePoint
{
public:
	GrapplePoint() = default;
	GrapplePoint(Vector2& p, float);
	~GrapplePoint();

	//jobs
	void Draw(aie::Renderer2D *renderer);
	void update(float Deltatime); //todo Impliment

	bool intersect(Sphere sphere);//todo Impliment
	bool intersect(AABB box);//todo Impliment
	bool intersect(Ray ray);//todo Impliment
	bool intersect(Plane plane);//todo Impliment
	//body.intersects(m_sphere, &intersect_point_sphere, &reflection_sphere) //todo Impliment

	void intersect(Grapple& grapple); //todo Impliment

	//parts
	Sphere body;
	Vector2 intersect_point;
	Vector2 reflection;

	

};

