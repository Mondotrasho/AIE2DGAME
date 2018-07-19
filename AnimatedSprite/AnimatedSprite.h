#pragma once
#include <vector>
#include <Texture.h>
const int DRAW_FLIP_X = 0x01;
const int DRAW_FLIP_Y = 0x04;// I know, the next bit is x02. This is used to
							 // demonstrate an assert in some cases
namespace aie {
	class Renderer2D;
};

class AnimatedSprite
{
private:
	struct Frame {
		aie::Texture* m_texture;
		float m_delay;
		Frame(aie::Texture* texture, float delay) : m_texture(texture), m_delay(delay) {}
	};

public:
	AnimatedSprite();
	~AnimatedSprite();

	void addFrame(aie::Texture* texture, float delay);

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer, int x, int y, int flags = 0);

private:
	std::vector<Frame> m_frames;
	int m_currentFrame;
	float m_timer;
};

