#include "SpriteObject.h"


bool SpriteObject::load(const char* filename) {
	delete m_texture;
	m_texture = nullptr;
	m_texture = new aie::Texture(filename);
	return m_texture != nullptr;
}

void SpriteObject::onDraw(aie::Renderer2D* renderer) {
	renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);
}