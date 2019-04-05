#pragma once
#include "Matrix3.h"
#include <vector>
#include "Texture.h"

namespace aie {
	class Renderer2D;
}

class Sprite
{
public:
	Sprite();
	~Sprite();

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer, float mod);

	const Matrix3& getLocalTransform() const;
	const Matrix3& getGlobalTransform() const;

	void updateTransform();
	void setPosition(float x, float y);
	void setRotate(float radians);
	void setScale(float width, float height);
	void translate(float x, float y);
	void rotate(float radians);
	void scale(float width, float height);

	bool load(const char* filename);
	aie::Texture* m_texture = nullptr;

protected:
	Matrix3 m_localTransform = Matrix3::identity;
	Matrix3 m_globalTransform = Matrix3::identity;

	Sprite* m_parent = nullptr;
	std::vector<Sprite*> m_children;

};
