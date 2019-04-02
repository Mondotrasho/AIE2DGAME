#include "_2DGameApp.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"

_2DGameApp::_2DGameApp() {

}
_2DGameApp::~_2DGameApp() {

}


bool _2DGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	InitializeNavMesh();
	InitializeSchools(10);	

	return true;
}

void _2DGameApp::shutdown() {

	delete m_navMesh;

	delete m_font;
	delete m_2dRenderer;
}



void _2DGameApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();
	
	UpdateSchools(deltaTime,input);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}



void _2DGameApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	DrawNavmesh(true,true,true);
	DrawSchools();
	// done drawing sprites
	m_2dRenderer->end();
}


void _2DGameApp::InitializeSchools(int num)
{
	Mouse = new GameObject;
	Mouse->position = Vector2(getWindowWidth() / 2 + 100, getWindowHeight() / 2 + 100);

	for (int i = 0; i < num; ++i)
	{
		auto freshfish = new GameObject;
		freshfish->position = Vector2(getWindowWidth() / 2, getWindowHeight() / 2);
		freshfish->speed = 600;

		auto follow = new FollowPathBehaviour();
		freshfish->behaviours.emplace_back(follow);

		auto pathfinder = new NewPathBehaviour(m_navMesh, freshfish->smoothPath);
		pathfinder->m_navMesh = m_navMesh;
		pathfinder->m_smoothPath = freshfish->smoothPath;// = NewPathBehaviour(m_navMesh, Fish->smoothPath);
		freshfish->behaviours.emplace_back(pathfinder);

		auto mousepath = new MouseGenPathBehaviour(m_navMesh, freshfish->smoothPath);
		mousepath->m_navMesh = m_navMesh;
		mousepath->m_smoothPath = freshfish->smoothPath;
		mousepath->settarget(Mouse);
		freshfish->behaviours.emplace_back(mousepath);

		Schools.push_back(freshfish);
		pathgenerators.push_back(pathfinder);
		followers.push_back(follow);
		mousepathgenerators.push_back(mousepath);

	}
}
void _2DGameApp::UpdateSchools(float delta_time, aie::Input* input)
{
	for (auto school : Schools)
	{
		school->Update(delta_time);
	}

	if (input->isMouseButtonDown(0))
		Mouse->position = Vector2(input->getMouseX(), input->getMouseY());

}
void _2DGameApp::DrawSchools()
{
	for (auto school : Schools)
	{
		m_2dRenderer->setRenderColour(0, 1, 0);
		if (!school->smoothPath.empty()) {
			//Vector2 last = school->smoothPath.front();
			//for (auto place : school->smoothPath)
			//{
			//	render->drawCircle(place.x, place.y, 2);
			//	render->drawLine(place.x, place.y, last.x, last.y, 1);
			//	last = place;
			//}
			//
			//render->setRenderColour(1, 0, 0);
			//last = school->path.front()->Pos;
			//for (auto place : school->path)
			//{
			//
			//	render->drawCircle(place->Pos.x, place->Pos.y, 2);
			//	render->drawLine(place->Pos.x, place->Pos.y, last.x, last.y, 1);
			//	last = place->Pos;
			//}
		}

	}

	for (auto school : Schools)
	{
		school->Draw(m_2dRenderer);
	}
}

void _2DGameApp::InitializeNavMesh()
{
	m_navMesh = new NavMesh(1280, 720);

	// just to help mess with the random 1 is asy to debug the pop issue
	srand(1);


	// random obstacles
	for (int i = 0; i < 12; ++i) {

		bool safe = false;
		do {
			safe = m_navMesh->addObstacle(rand() / float(RAND_MAX) * getWindowWidth() * 0.75f + getWindowWidth() * 0.125f,
				rand() / float(RAND_MAX) * getWindowHeight() * 0.75f + getWindowHeight() * 0.125f,
				60, 60,
				10);
		} while (safe == false);
	}

	m_navMesh->build();
}
void _2DGameApp::DrawNavmesh(bool drawobstacles, bool drawpoly, bool drawnode)
{
	// draw nav mesh polygons
	for (auto node : m_navMesh->getNodes()) {

		m_2dRenderer->setRenderColour(1, 1, 0);
		if (drawpoly) {
			m_2dRenderer->drawLine(node->vertices[0].x, node->vertices[0].y, node->vertices[1].x, node->vertices[1].y);
			m_2dRenderer->drawLine(node->vertices[1].x, node->vertices[1].y, node->vertices[2].x, node->vertices[2].y);
			m_2dRenderer->drawLine(node->vertices[2].x, node->vertices[2].y, node->vertices[0].x, node->vertices[0].y);
		}
		m_2dRenderer->setRenderColour(1, 1, 0);
		if (drawnode) {
			node->Draw(m_2dRenderer);
		}
	}

	// draw obstacles
	if (drawobstacles) {
		m_2dRenderer->setRenderColour(1, 0, 0);
		for (auto& o : m_navMesh->getObstacles()) {
			m_2dRenderer->drawBox(o.x + o.w * 0.5f, o.y + o.h * 0.5f, o.w, o.h);
		}
	}
}