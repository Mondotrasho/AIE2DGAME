#include "LevelManager.h"
#include "Renderer2D.h"
#include "Application.h"


//random start colour currently set todo make random maybe tweening / easing for update
LevelManager::LevelManager() : m_colour(0.3f,0.7f,0.0f)
{
}


LevelManager::~LevelManager()
{
}
//Takes box of planes and the renderer 
//get the middle point using the app and get window width and height
void LevelManager::draw_boundries(std::vector<Plane>& planes, aie::Renderer2D* render, aie::Application& app)
{
	for (auto plane : planes)
	{
		// get point on plane closest to window center 
		auto closesttomid = plane.closestPoint(Vector2(app.getWindowWidth() /2 , app.getWindowHeight() / 2));
		render->setRenderColour(1, 0, 1);

		// draw plane normal 50 pixels long 
		render->setRenderColour(1, 0, 0);
		render->drawLine(
			closesttomid.x, closesttomid.y,	//the closest point
			closesttomid.x + plane.N.x * 50,//that x point in the direction of the Normal by 50 pix
			closesttomid.y + plane.N.y * 50,//that y point in the direction of the Normal by 50 pix
			4);								//4 thick

		// get a vector perpendicular to the normal 
		Vector2 v(plane.N.y, -plane.N.x);

		// draw separating line 3000 pixels long 
		render->setRenderColour(1, 1, 0);
		render->drawLine(
			closesttomid.x - v.x * 1500,
			closesttomid.y - v.y * 1500,
			closesttomid.x + v.x * 1500,
			closesttomid.y + v.y * 1500,
			4);
	}

}

void LevelManager::RandomizeColours(float deltatime)
{//colour changing
	//0.0 is lowest 1.0 is heighest
	m_colour.R += deltatime / 2;
	if (m_colour.R > 1) { m_colour.R = 0; }
	m_colour.G += deltatime / 2;
	if (m_colour.G > 1) { m_colour.G = 0; }
	m_colour.B += deltatime / 2;
	if (m_colour.B > 1) { m_colour.B = 0; }
}
