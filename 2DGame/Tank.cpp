#include "Tank.h"
#include "Input.h"


Tank::Tank()
{
}

Tank::Tank(const char* tankImage, const char* turretImage)
{
	load(tankImage);
	m_turret.load(turretImage);

	// attach turret to top of tank
	addChild(&m_turret);
	
}

Tank::~Tank()
{
}


void Tank::setup(const char* tankImage, const char* turretImage)
{
	load(tankImage);
	m_turret.load(turretImage);

	// attach turret to top of tank
	addChild(&m_turret);
	

}

void Tank::onUpdate(float deltaTime)
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	// rotate tank, using deltaTime as the rotation speed
	if (input->isKeyDown(aie::INPUT_KEY_A))
		rotate(deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_D))
		rotate(-deltaTime);

	// move tank, the 100 magic-number represents speed
	if (input->isKeyDown(aie::INPUT_KEY_W)) { 
		auto facing = getLocalTransform()[1] * deltaTime * 100;
		translate(facing.x, facing.y);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		auto facing = getLocalTransform()[1] *deltaTime * -100;
		translate(facing.x, facing.y);
	}


	// rotate turret
	if (input->isKeyDown(aie::INPUT_KEY_Q))
		m_turret.rotate(deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_E))
		m_turret.rotate(-deltaTime);


}
