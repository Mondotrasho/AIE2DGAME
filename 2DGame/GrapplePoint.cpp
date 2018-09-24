#include "GrapplePoint.h"
#include "Renderer2D.h"
GrapplePoint::GrapplePoint(Vector2& p, float r)
{
	body = { p,r };
}


GrapplePoint::~GrapplePoint()
{
}

void GrapplePoint::Draw(aie::Renderer2D *renderer)
{
	renderer->setRenderColour(0.0f, 0.3f, 0.2f);
	renderer->drawCircle(body.center.x, body.center.y, body.radius);
}


