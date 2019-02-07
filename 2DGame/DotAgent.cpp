#include "DotAgent.h"
#include "Renderer2D.h"


DotAgent::DotAgent()
{
}

void DotAgent::Draw(aie::Renderer2D* renderer)
{
	renderer->drawCircle(m_Position.x, m_Position.y, dotSize);
}
