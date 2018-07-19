#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "ResouceManager.h"

struct Vector2D {
	float x;
	float y;
};

class AnimatedSpriteApp : public aie::Application {
public:

	AnimatedSpriteApp();
	virtual ~AnimatedSpriteApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	AnimatedSprite		m_sprite, m_sprite2, m_sprite3;
	Vector2D			m_position, m_position2, m_position3;
	ResourceManager<aie::Texture> m_images;
	
};