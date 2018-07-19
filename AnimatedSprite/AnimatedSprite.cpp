#include "AnimatedSprite.h"
#include <Renderer2D.h>
#include <cassert>


AnimatedSprite::AnimatedSprite() : m_currentFrame(0), m_timer(0)
{	
}


AnimatedSprite::~AnimatedSprite()
{
	for (Frame f : m_frames) {
		delete f.m_texture.get();
	}
}

void AnimatedSprite::addFrame(const std::shared_ptr<aie::Texture>& texture, float delay)
{	assert(texture);
	m_frames.push_back(Frame(texture, delay));
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

void AnimatedSprite::draw(aie::Renderer2D* renderer, int x, int y, int flags)
{
	Frame frame = m_frames.at(m_currentFrame);
	switch (flags) {
	case 0: {
		renderer->drawSprite(frame.m_texture.get(), x, y);
		break;
	}
	case DRAW_FLIP_X: {
		renderer->setUVRect(0.0f, 0.0f, -1.0f, 1.0f);
		renderer->drawSprite(frame.m_texture.get(), x, y);
		renderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}
	case DRAW_FLIP_Y: {
		renderer->setUVRect(0.0f, 0.0f, 1.0f, -1.0f);
		renderer->drawSprite(frame.m_texture.get(), x, y);
		renderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}
	case DRAW_FLIP_X | DRAW_FLIP_Y: {
		renderer->setUVRect(0.0f, 0.0f, -1.0f, -1.0f);
		renderer->drawSprite(frame.m_texture.get(), x, y);
		renderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	}
	default:
		throw std::exception((std::string("Invalid flag value: ") +
			std::to_string(flags)).c_str());
		
	}
}