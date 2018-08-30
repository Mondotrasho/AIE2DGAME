#include "TreeNode_john.h"
#include <string>

extern aie::Font* g_systemFont;

TreeNode_john::TreeNode_john(TreeNode_john* parent, int value) : m_parent(parent), m_value(value)
{
}


TreeNode_john::~TreeNode_john()
= default;

void TreeNode_john::draw(aie::Renderer2D* renderer, int x, int y, bool selected) const
{
	static char buffer[10];

	sprintf_s(buffer, "%d", m_value);

	renderer->setRenderColour(1, 1, 0);
	renderer->drawCircle(x, y, 30);

	if (selected)
		renderer->setRenderColour(.5, .5, 0);
	else
		renderer->setRenderColour(0, 0, 0);
	renderer->drawCircle(x, y, 28,0);

	renderer->setRenderColour(1,0, 0);
	renderer->drawText(g_systemFont, buffer, x - 12, y - 10 , 10);
}
