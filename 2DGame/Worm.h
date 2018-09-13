#pragma once
#include "SpriteObject.h"
#include "Plane.h"

class Worm  : public SpriteObject{

	public:

	// create uninitialized Worm
	Worm();
	
	// load sprites and attach Worm
	Worm(const char* WormImage, const char* worm_body_image);
	virtual ~Worm();
	
	// OTHER load sprites and attach Worm
	void setup(const char* WormImage, const char* worm_body_image);

	// update Worm/WormBody movement
	virtual void onUpdate(float deltaTime,std::vector<Plane>& planes);
	Vector3 velocity = { 3.92720675 ,3.92720675 ,0 };
	int worm_states;
	Sphere worm_face;

	bool checkCollision(Vector2 origin);
	private:

	SpriteObject m_body1, m_body2, m_body3, m_body4, m_body5, m_body6;
	
	// add speed variables

};

