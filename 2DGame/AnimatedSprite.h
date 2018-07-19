#pragma once
#include <vector>
#include <Texture.h>
#include <memory>

const int DRAW_FLIP_X = 0x01;
const int DRAW_FLIP_Y = 0x02;

const int NO_ERROR = 0;
const int ERROR_NULL_TEXTURE = -1;
const int ERROR_NO_PIXEL_DATA = -2;

namespace aie {
	class Renderer2D;
};

class AnimatedSprite
{
private:
	struct Frame {
		std::shared_ptr<aie::Texture> m_texture;
		float m_delay;
		Frame(const std::shared_ptr<aie::Texture>& texture, float delay) : m_texture(texture), m_delay(delay) {}
	};

public:
	AnimatedSprite();
	~AnimatedSprite();

	int addFrame(const std::shared_ptr<aie::Texture>& texture, float delay);

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer, int x, int y, float rotation=0, int flags=0);

	int getCurrentFrame() { return m_currentFrame; }
	int getFrameCount() { return m_frames.size(); }

private:
	std::vector<Frame> m_frames;
	int m_currentFrame;
	float m_timer;
};

