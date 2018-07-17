#pragma once
#include "SpriteObject.h"
class Tank : public SpriteObject{

	public:

	// create uninitialized tank
	Tank();
	
	// load sprites and attach turret
	Tank(const char* tankImage, const char* turretImage);
	virtual ~Tank();
	
	// load sprites and attach turret
	void setup(const char* tankImage, const char* turretImage);

	// update tank/turret movement
	virtual void onUpdate(float deltaTime);



	private:

	SpriteObject m_turret;
	// add speed variables
};

