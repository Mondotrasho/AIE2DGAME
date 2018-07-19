#include "AnimatedSprite.h"
#include <Renderer2D.h>
#include <assert.h>
#include <iostream>
#include <exception>
#include <string>

AnimatedSprite::AnimatedSprite() : m_currentFrame(0), m_timer(0)
{	
}


AnimatedSprite::~AnimatedSprite()
{
}

int AnimatedSprite::addFrame(const std::shared_ptr<aie::Texture>& texture, float delay)
{
	if (texture.get() == nullptr)
		return ERROR_NULL_TEXTURE;

	if (texture->getPixels() == nullptr)
		return ERROR_NO_PIXEL_DATA;

	m_frames.push_back(Frame(texture, delay));
	return NO_ERROR;
}


void AnimatedSprite::update(float deltaTime)
{
	m_timer += deltaTime;

	if (m_timer >= m_frames.at(m_currentFrame).m_delay) {
		m_timer -= m_frames.at(m_currentFrame).m_delay;
		m_currentFrame++;
		if (m_currentFrame >= m_frames.size())
			m_currentFrame = 0;
	}
}

void AnimatedSprite::draw(aie::Renderer2D* renderer, int x, int y, float rotation, int flags)
{	
	Frame frame = m_frames.at(m_currentFrame);
	
	switch (flags) {
	case 0: {
		renderer->drawSprite(frame.m_texture.get(), x, y, 0, 0, rotation);
		break;
	}
	case DRAW_FLIP_X: {
		renderer->setUVRect(0.0f, 0.0f, -1.0f, 1.0f);
		renderer->drawSprite(frame.m_texture.get(), x, y, 0, 0, rotation);
		renderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}
	case DRAW_FLIP_Y: {
		renderer->setUVRect(0.0f, 0.0f, 1.0f, -1.0f);
		renderer->drawSprite(frame.m_texture.get(), x, y, 0, 0, rotation);
		renderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}
	case DRAW_FLIP_X | DRAW_FLIP_Y: {
		renderer->setUVRect(0.0f, 0.0f, -1.0f, -1.0f);
		renderer->drawSprite(frame.m_texture.get(), x, y, 0, 0, rotation);
		renderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}
	default:
		break;
	}
}