#include "Sprite.h"
#include "Renderer2D.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::update(float deltaTime)
{
}

void Sprite::draw(aie::Renderer2D* renderer, float mod = 0)
{
	if(mod == 0)
	{ //vannila
		renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);
	}
	else
	{ //with rectangular scale (for fish)
		renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform, 2.5 * mod, 10 * mod);
	}

}

const Matrix3& Sprite::getLocalTransform() const
{
	return m_localTransform;
}

const Matrix3& Sprite::getGlobalTransform() const
{
	return m_globalTransform;
}

void Sprite::updateTransform()
{
	if (m_parent != nullptr)
		m_globalTransform = m_parent->m_globalTransform *
		m_localTransform;
	else
		m_globalTransform = m_localTransform;
	for (auto child : m_children)
		child->updateTransform();
}

void Sprite::setPosition(float x, float y)
{
	m_localTransform[2] = { x, y, 1 };
	updateTransform();
}

void Sprite::setRotate(float radians)
{
	m_localTransform.setRotateZ(radians);
	updateTransform();
}

void Sprite::setScale(float width, float height)
{
	m_localTransform.set_scaled(width, height);
	updateTransform();
}

void Sprite::translate(float x, float y)
{
	m_localTransform.translate(x, y);
	updateTransform();
}

void Sprite::rotate(float radians)
{
	m_localTransform.rotate_z(radians);
	updateTransform();
}

void Sprite::scale(float width, float height)
{
	m_localTransform.scale(width, height);
	updateTransform();
}

bool Sprite::load(const char* filename)
{
	delete m_texture;
	m_texture = nullptr;
	m_texture = new aie::Texture(filename);
	return m_texture != nullptr;
}
