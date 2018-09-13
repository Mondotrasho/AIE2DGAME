#include "Worm.h"
#include "Input.h"
int minmax(int i)
{
	int max = 3;
	int min = 0;


	if (i > max) { return min; }
	if (i < min) { return max; }

	return i ;
}

Worm::Worm()
{
	done = false;
}

Worm::Worm(const char* WormImage, const char* worm_body_image)
{


	load(WormImage);
	m_body1.load(worm_body_image);
	m_body2.load(worm_body_image);
	m_body3.load(worm_body_image);
	m_body4.load(worm_body_image);
	m_body5.load(worm_body_image);
	m_body6.load(worm_body_image);

	// attach Wormbody to top of Worm
	addChild(&m_body1);
	m_body1.scale(0.9, 0.9);
	m_body1.setPosition(0, -60);
	m_body1.addChild(&m_body2);
	m_body2.scale(0.9, 0.9);
	m_body2.setPosition(0, -60);
	m_body2.addChild(&m_body3);
	m_body3.scale(0.9, 0.9);
	m_body3.setPosition(0, -60);
	m_body3.addChild(&m_body4);
	m_body4.scale(0.9, 0.9);
	m_body4.setPosition(0, -60);
	m_body4.addChild(&m_body5);
	m_body5.scale(0.9, 0.9);
	m_body5.setPosition(0, -60);
	m_body5.addChild(&m_body6);


}


void Worm::setup(const char* WormImage, const char* worm_body_image)
{
	//shrink
	scale(0.5, 0.5);
	//load textures
	load(WormImage);
	m_body1.load(worm_body_image);
	m_body2.load(worm_body_image);
	m_body3.load(worm_body_image);
	m_body4.load(worm_body_image);
	m_body5.load(worm_body_image);
	m_body6.load(worm_body_image);

	//attach body segments
	addChild(&m_body1);
	m_body1.scale(0.9, 0.9);
	m_body1.setPosition(0, -60);
	m_body1.addChild(&m_body2);
	m_body2.scale(0.9,0.9);
	m_body2.setPosition(0,-60);
	m_body2.addChild(&m_body3);
	m_body3.scale(0.9, 0.9);
	m_body3.setPosition(0, -60);
	m_body3.addChild(&m_body4);
	m_body4.scale(0.9, 0.9);
	m_body4.setPosition(0, -60);
	m_body4.addChild(&m_body5);
	m_body5.scale(0.9, 0.9);
	m_body5.setPosition(0, -60);
	m_body5.addChild(&m_body6);
	

}

void Worm::onUpdate(float deltaTime, std::vector<Plane>& planes)
{
	// input example
	aie::Input* input = aie::Input::getInstance();	
	// rotate Worm
	if (worm_states == 1) {
		rotate(-deltaTime);

	m_body1.rotate(0.4f * deltaTime);
	m_body2.rotate(0.4f * deltaTime);
	m_body3.rotate(0.4f * deltaTime);
	m_body4.rotate(0.4f * deltaTime);
	m_body5.rotate(0.4f * deltaTime);
	m_body5.rotate(0.4f * deltaTime);
	//rotate(-deltaTime*3);
}
if (worm_states == 2) {
	rotate(deltaTime);
	m_body1.rotate(-0.4f * deltaTime);
	m_body2.rotate(-0.4f * deltaTime);
	m_body3.rotate(-0.4f * deltaTime);
	m_body4.rotate(-0.4f * deltaTime);
	m_body5.rotate(-0.4f * deltaTime);
	m_body5.rotate(-0.4f * deltaTime);
}

	//correct rotation
if (m_body1.getLocalTransform().x_axis.y < 0) {
	m_body1.rotate(0.3f* deltaTime);
	m_body2.rotate(0.3f* deltaTime);
	m_body3.rotate(0.3f* deltaTime);
	m_body4.rotate(0.3f* deltaTime);
	m_body5.rotate(0.3f* deltaTime);
	m_body6.rotate(0.3f* deltaTime);
}
if (m_body1.getLocalTransform().x_axis.y > 0) {
	m_body1.rotate(-0.3f* deltaTime);
	m_body2.rotate(-0.3f* deltaTime);
	m_body3.rotate(-0.3f* deltaTime);
	m_body4.rotate(-0.3f* deltaTime);
	m_body5.rotate(-0.3f* deltaTime);
	m_body6.rotate(-0.3f* deltaTime);
}
float multi = 1.0f;
	for (int i = 0; i < 4; ++i)
	{

		//top and bottom planes
		if (planes.at(i).N.x == 0 && planes.at(i).distanceTo(worm_face.closestPoint(planes.at(i).closestPoint(worm_face.center))) < 10)
		{
			if (planes.at(i).distanceTo(worm_face.closestPoint(planes.at(i).closestPoint(worm_face.center))) && planes.at(minmax(i+1)).distanceTo(worm_face.closestPoint(planes.at(minmax(i + 1)).closestPoint(worm_face.center))))
			{
				if (planes.at(i).N.y == 1 && planes.at(minmax(i + 1)).N.x == 1) {
					auto facing = getLocalTransform()[1];
					translate(facing.x*-velocity.x + multi, facing.y + multi);
					updateTransform();

				}
				if (planes.at(i).N.y == 1 && planes.at(minmax(i + 1)).N.x == -1) {
					auto facing = getLocalTransform()[1];
					translate(facing.x*-velocity.x - multi, facing.y + multi);
					updateTransform();

				}
			}
			if (planes.at(i).N.y == 1) {
				auto facing = getLocalTransform()[1];
				translate(facing.x, facing.y*-velocity.y + multi);
				updateTransform();
			}
			if (planes.at(i).N.y == -1) {
				auto facing = getLocalTransform()[1];
				translate(facing.x, facing.y*-velocity.y - multi);
				updateTransform();
			}

		}
		//left and right planes
		if (planes.at(i).N.y == 0 && planes.at(i).distanceTo(worm_face.closestPoint(planes.at(i).closestPoint(worm_face.center))) < 10)
		{
			if (planes.at(i).distanceTo(worm_face.closestPoint(planes.at(i).closestPoint(worm_face.center)))&& planes.at(minmax(i + 1)).distanceTo(worm_face.closestPoint(planes.at(minmax(i + 1)).closestPoint(worm_face.center))))
			{
				if (planes.at(i).N.x == 1 && planes.at(minmax(i + 1)).N.y == 1) {
					auto facing = getLocalTransform()[1];
					translate(facing.x*-velocity.x + multi, facing.y + multi);
					updateTransform();

				}
				if (planes.at(i).N.x == 1 && planes.at(minmax(i + 1)).N.y == -1) {
					auto facing = getLocalTransform()[1];
					translate(facing.x*-velocity.x + multi, facing.y - multi);
					updateTransform();

				}
			}
			if (planes.at(i).N.x == 1) {
				auto facing = getLocalTransform()[1];
				translate(facing.x*-velocity.x + multi, facing.y );
				updateTransform();

			}
			if (planes.at(i).N.x == -1) {
				auto facing = getLocalTransform()[1];
				translate(facing.x*-velocity.x - multi, facing.y );
				updateTransform();
			}
		}
	}
auto facing = getLocalTransform()[1];
translate(facing.x*velocity.x, facing.y*velocity.y);
updateTransform();

}
