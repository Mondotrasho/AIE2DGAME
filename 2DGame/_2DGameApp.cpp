

#include "_2DGameApp.h"
#include "Font.h"
#include "RayController.h"
#include "PointController.h"

_2DGameApp::_2DGameApp()
{
}

_2DGameApp::~_2DGameApp() {

}

bool _2DGameApp::startup() {

	m_2dRenderer = new aie::Renderer2D();

	//Temp variables for readability
	Vector2 startypoint = { 640, 360 }; // X = 640 Y = 360
	Vector2 directionypoint = { 0.7f, 0.7f }; //start pointing up 0.7 of the way and across 0.7 of the way

	//make the ray starting where it starts pointing where it points and 300 long
	m_ray = Ray(startypoint, directionypoint, 700);
	//use atan2 to get angle from y and x WHY?? Y THEN X CAUSE FUCK U THATS WHY??
	m_rayAngle = atan2(directionypoint.y, directionypoint.x);

	m_colour = { 0.3f,0.7f,0.0f };

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_timer = 0;

	m_point = { m_ray.origin.x + 100,m_ray.origin.y };
	
	box.push_back(GrapplePoint(Vector2(440, 660), 30));
	box.push_back(GrapplePoint(Vector2(240, 660), 30));
	box.push_back(GrapplePoint(Vector2(440, 660), 30));
	box.push_back(GrapplePoint(Vector2(640, 660), 30));
	box.push_back(GrapplePoint(Vector2(840, 660), 30));
	box.push_back(GrapplePoint(Vector2(1040, 660), 30));


	m_plane = { Vector2(400, 3),Vector2(401,3) };//{ Vector2(0.0f,0.1f),-50 }; //use this format for rotating as the 0.1 0.2 etc is easier for for loops and shite
	return true;
}

void _2DGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}



void _2DGameApp::update(float deltaTime) {

	m_timer += deltaTime;
	//0.0 - 1.0
	m_colour.R += deltaTime / 2;
	if (m_colour.R > 1) { m_colour.R = 0; }
	m_colour.G += deltaTime / 2;
	if (m_colour.G > 1) { m_colour.G = 0; }
	m_colour.B += deltaTime / 2;
	if (m_colour.B > 1) { m_colour.B = 0; }
	raycontroller(m_ray,m_rayAngle,m_plane,deltaTime);
	pointcontroller(m_point, deltaTime);
	if (m_ray.origin.distance(m_plane.closestPoint(m_ray.origin)) < 10) { m_ray.origin.y += 200 * deltaTime; }

	
	// input example
	aie::Input* input = aie::Input::getInstance();
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void _2DGameApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	
	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	
	
	// draw a pink/purle ray
	m_2dRenderer->setRenderColour(m_colour.R, m_colour.G, m_colour.B);
	m_2dRenderer->drawCircle(m_ray.origin.x, m_ray.origin.y, 10);
	m_2dRenderer->drawLine(m_ray.origin.x, m_ray.origin.y,
		m_ray.origin.x + m_ray.direction.x *
		m_ray.length,
		m_ray.origin.y + m_ray.direction.y *
		m_ray.length, 5);

	//point Move for closest position on a ray to a point
	//point IJKL
	m_2dRenderer->drawCircle((m_point.x), (m_point.y), 10);
	//line to ray
	const auto closepoint = m_ray.closestPoint(m_point);
	m_2dRenderer->setRenderColour(.3f, .3f, .3f);
	m_2dRenderer->drawLine(m_point.x, m_point.y, closepoint.x, closepoint.y, 1);

	//ray vs Sphere 
	
	m_2dRenderer->setRenderColour(m_colour.R, m_colour.G, m_colour.B);

	for (auto& Grappleable : box)
	{
		Grappleable.Draw(m_2dRenderer, test);
	}

	//ray vs plane
	m_2dRenderer->setRenderColour(m_colour.R, m_colour.G, m_colour.B);

	// get point on plane closest to window center 
	auto u = m_plane.closestPoint(Vector2(640,360));
	m_2dRenderer->setRenderColour(1, 0, 1);
	
	// draw plane normal 50 pixels long 
	m_2dRenderer->setRenderColour(1, 0, 0); 
	m_2dRenderer->drawLine(u.x, u.y, u.x + m_plane.N.x * 50, u.y + m_plane.N.y * 50, 4);

	// get a vector perpendicular to the normal 
	Vector2 v(m_plane.N.y, -m_plane.N.x);

	// draw separating line 3000 pixels long 
	m_2dRenderer->setRenderColour(1, 1, 0); 
	m_2dRenderer->drawLine(u.x - v.x * 1500, u.y - v.y * 1500, u.x + v.x * 1500, u.y + v.y * 1500, 4);
	
	Vector2 intersect_point_plane;
	Vector2 reflection_plane;
	if(m_ray.intersects(m_plane, &intersect_point_plane, &reflection_plane))
	{	m_2dRenderer->setRenderColour(.3f, .3f, .3f);
		m_2dRenderer->drawCircle((intersect_point_plane.x), (intersect_point_plane.y), 10);
		auto temp = intersect_point_plane + reflection_plane;
		m_2dRenderer->drawLine((intersect_point_plane.x), (intersect_point_plane.y), temp.x, temp.y);
	}
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

