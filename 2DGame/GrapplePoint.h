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
	void update(float Deltatime);

	bool intersect(Sphere sphere);
	bool intersect(AABB box);
	bool intersect(Ray ray);
	bool intersect(Plane plane);
	//body.intersects(m_sphere, &intersect_point_sphere, &reflection_sphere)

	void intersect(Grapple& grapple);

	//parts
	Sphere body;

	Vector2 intersect_point;
	Vector2 reflection;

	

};

