#pragma once
#include "SceneObject.h"
#include "Texture.h"

class SpriteObject : public SceneObject {
public:
	SpriteObject() {}
	SpriteObject(const char* filename) { load(filename); }
	virtual ~SpriteObject() { if(m_texture != 0xdddddddd) delete m_texture; }
	bool load(const char* filename);
	virtual void onDraw(aie::Renderer2D* renderer);

protected:
	aie::Texture* m_texture = nullptr;
};
