#pragma once
#include "Component.h"
#include "Matrix3.h"

class CMove :
	public Component
{
	
public:
	CMove();
	virtual ~CMove() = 0;

	void update(float deltaTime);

	void setPosition(float x, float y);
	void setRotate(float radians);
	void setScale(float width, float height);
	void translate(float x, float y);
	void rotate(float radians);
	void scale(float width, float height);

	Matrix3 getTransform();
private:
	Matrix3 Transform = Matrix3::identity;
};

