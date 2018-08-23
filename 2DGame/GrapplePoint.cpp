#include "GrapplePoint.h"

GrapplePoint::GrapplePoint(Vector2& p, float r)
{
	body = { p,r };
}


GrapplePoint::~GrapplePoint()
{
}

void GrapplePoint::Draw(aie::Renderer2D *renderer, Grapple& grapple)
{
	renderer->setRenderColour(.3f, .3f, .3f);
	//^^may not be needed ^^
	renderer->drawCircle(body.center.x, body.center.y, body.radius);
	
	//
	if (grapple.get_ray().intersects(body, &intersect_point, &reflection))
	{
		
		renderer->drawCircle((intersect_point.x), (intersect_point.y), 10);
		auto temp = reflection + intersect_point * (grapple.get_ray().length - grapple.get_ray().origin.distance(intersect_point) );
		renderer->drawLine((intersect_point.x), (intersect_point.y), temp.x, temp.y);
	}
	
}


