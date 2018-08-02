#pragma once
#include "Component.h"
#include "SpriteObject.h"

class CDraw : public Component
{
public:
	CDraw();
	virtual ~CDraw();

	void set_texture(aie::Texture* new_texture)
	{
		m_texture = new_texture;
	}

	void draw(aie::Renderer2D* renderer);
private:
	aie::Texture* m_texture;
};

