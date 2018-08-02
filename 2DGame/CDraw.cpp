#include "CDraw.h"
#include "GameObject.h"


CDraw::CDraw()
{
}


CDraw::~CDraw()
{
}

void CDraw::draw(aie::Renderer2D* renderer)
{
	renderer->drawSprite(m_texture, 200, 200, 100, 100);
}
