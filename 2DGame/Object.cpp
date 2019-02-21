#include "Object.h"


Object::Object()
= default;

Object::~Object()
= default;

void Object::draw(aie::Renderer2D* rend)
{
	rend->drawCircle(pos.x, pos.y, size);
}
