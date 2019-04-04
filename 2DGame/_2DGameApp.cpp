#include "_2DGameApp.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"
#include "FishFood.h"
#include "algorithm"

_2DGameApp::_2DGameApp() {

}
_2DGameApp::~_2DGameApp() {

}


bool _2DGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	InitializeNavMesh();
	InitializeSchools(10, false);	

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
	
	UpdategameObjects(deltaTime,input);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}



void _2DGameApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	DrawNavmesh(true, false, false);
	DrawgameObjects(true, false, false);

	// done drawing sprites
	m_2dRenderer->end();
}


void _2DGameApp::InitializeSchools(int num,bool randspeed)
{

	


	//mouse pos object
	//Mouse = new GameObject(Vector2(getWindowWidth() / 2 + 100, getWindowHeight() / 2 + 100),0,&Pool);

	for (int i = 0; i < num; ++i)
	{

		FishShool* freshfish;
		//make schools
		//rand teams
		switch (rand() % 2)
		{
		case 0:freshfish = new FishShool(Vector2(getWindowWidth() / 2, getWindowHeight() / 2), 0, &Pool, nullptr, Blue);
			break;
		case 1: freshfish = new FishShool(Vector2(getWindowWidth() / 2, getWindowHeight() / 2), 0, &Pool, nullptr, Red);
			break;
		default:freshfish = new FishShool(Vector2(getWindowWidth() / 2, getWindowHeight() / 2), 0, &Pool, nullptr, None); ;
		}

		//auto freshfish = new FishShool(Vector2(getWindowWidth() / 2, getWindowHeight() / 2),0, &Pool,nullptr,Blue);
		if(randspeed)
		{
			freshfish->set_speed(10 + (rand() % 600));
		}
		else
		{
			freshfish->set_speed(300);
		}
		
		freshfish->size = 1;

		//follow specifics
		ActionMoveAlongPath* follow = new ActionMoveAlongPath();

		//randpath specifics
		ActionIdle* pathfinder = new ActionIdle(m_navMesh);

		FindMyNode* nodefind = new FindMyNode(m_navMesh);

		//the selector/OR for everything
		Selector* orer = new Selector();

		CheckInRangeOfEdibleFish* fishrange = new CheckInRangeOfEdibleFish(m_navMesh, 400);
		ActionPathToMovingTarget* findfishpath = new ActionPathToMovingTarget(m_navMesh);
		ActionMoveAlongPath* followfishpath = new ActionMoveAlongPath();
		CheckIfInRangeOfTarget* amiinfishrange = new CheckIfInRangeOfTarget(10);
		ActionEatFish* eatfish = new ActionEatFish(101);

		CheckInRangeOfFood* foodrange = new CheckInRangeOfFood(m_navMesh,400);
		ActionPathToTarget* findfoodpath = new ActionPathToTarget(m_navMesh);
		ActionMoveAlongPath* followfoodpath = new ActionMoveAlongPath();
		CheckIfInRangeOfTarget* amiinfoodrange = new CheckIfInRangeOfTarget(10);
		ActionEatFood* eatfood = new ActionEatFood(101);

		

		//the sequence/AND for fish eating
		//
		auto fishdo = new Sequence();
		fishdo->children.push_back(nodefind);
		fishdo->children.push_back(fishrange);
		fishdo->children.push_back(findfishpath);
		fishdo->children.push_back(followfishpath);
		fishdo->children.push_back(amiinfishrange);
		fishdo->children.push_back(eatfish);


		//the sequence/AND for food eating
		//
		auto fooddo = new Sequence();
		fooddo->children.push_back(nodefind);
		fooddo->children.push_back(foodrange);
		fooddo->children.push_back(findfoodpath);
		fooddo->children.push_back(followfoodpath);
		fooddo->children.push_back(amiinfoodrange);
		fooddo->children.push_back(eatfood);

		//the sequence/AND for idle
		//fist is finds where it is then it trys to move along its path and finaly it makes a new path
		auto idledo = new Sequence();
		idledo->children.push_back(nodefind);
		idledo->children.push_back(follow);
		idledo->children.push_back(pathfinder);

		//orer->children.push_back(nodefind);
		orer->children.push_back(fishdo);
		orer->children.push_back(fooddo);
		orer->children.push_back(idledo);

		//add the idle sequence directly
		freshfish->addbehaviour(orer);

		//pool add
		//freshfish->ObjectPool = Pool;

		//push to storage
		Pool.push_back(freshfish);	
	}
}
bool notdone = true;
void _2DGameApp::UpdategameObjects(float delta_time, aie::Input* input)
{
	if (timer > 0) { timer -= delta_time; }

	//clean pool
	for (int i = 0; i < Pool.size();)
	{
		if (Pool[i]->deleteme) {
			std::vector<GameObject*>::iterator itposition = std::find(Pool.begin(), Pool.end(), Pool[i]);
			Pool.erase(itposition);
			break;
		}
		i++;
	}
	//update pool
	for (auto object : Pool)
	{
		object->Update(delta_time);
	}

	if ((rand() % 200 == 1))
	{
		auto newnodefinder = new FindMyNode(m_navMesh);
		FishFood* newfood;
		switch (rand() % 2) {
		case 1:newfood = new FishFood(Vector2(rand() % getWindowWidth(), rand() % getWindowHeight()), 0, &Pool, nullptr, Blue);
			break;
		case 0: newfood = new FishFood(Vector2(rand() % getWindowWidth(), rand() % getWindowHeight()), 0, &Pool, nullptr, Red);
			break;
		default: newfood = new FishFood(Vector2(rand() % getWindowWidth(), rand() % getWindowHeight()), 0, &Pool, nullptr, None);
		}
		newfood->addtopool();
		newfood->addbehaviour(newnodefinder);
		nodefinders.emplace_back(newnodefinder);
	}
	if (input->isMouseButtonDown(0) && timer < 0.1f)
	{
		auto newnodefinder = new FindMyNode(m_navMesh);
		FishFood* newfood = new FishFood(Vector2(input->getMouseX(), input->getMouseY()), 0, &Pool, nullptr, Blue);
		newfood->addtopool();
		newfood->addbehaviour(newnodefinder);
		nodefinders.emplace_back(newnodefinder);
		timer = 0.3f;
	}
	if (input->isMouseButtonDown(1) && timer < 0.1f)
	{
		auto newnodefinder = new FindMyNode(m_navMesh);
		FishFood* newfood = new FishFood(Vector2(input->getMouseX(), input->getMouseY()), 0, &Pool, nullptr, Red);
		newfood->addtopool();
		newfood->addbehaviour(newnodefinder);
		nodefinders.emplace_back(newnodefinder);
		timer = 0.3f;
	}
}
void _2DGameApp::DrawgameObjects(bool drawobjects, bool drawpath, bool drawsmoothpath)
{

	//Mouse->Draw(m_2dRenderer);

	for (auto object : Pool)
	{
		//smooth draw specifics
		if (drawsmoothpath)
		{
			m_2dRenderer->setRenderColour(0, 1, 0);
			if (!object->smoothPath.empty())
			{
				Vector2 last = object->smoothPath.front();
				for (auto place : object->smoothPath)
				{
					m_2dRenderer->drawCircle(place.x, place.y, 2);
					m_2dRenderer->drawLine(place.x, place.y, last.x, last.y, 1);
					last = place;
				}
			}
		}

		//path draw specifics
		if (drawpath) {
			m_2dRenderer->setRenderColour(1, 0, 0);
			if (!object->path.empty())
			{

				Vector2 last = object->path.front()->Pos;
				for (auto place : object->path)
				{

					m_2dRenderer->drawCircle(place->Pos.x, place->Pos.y, 2);
					m_2dRenderer->drawLine(place->Pos.x, place->Pos.y, last.x, last.y, 1);
					last = place->Pos;
				}
			}
		}

		//schools draw specifics
		if (drawobjects)
		{
			m_2dRenderer->setRenderColour(0, 0, 1);
			object->Draw(m_2dRenderer);
		}
	}
}

void _2DGameApp::InitializeNavMesh()
{
	m_navMesh = new NavMesh(1280, 720);

	// just to help mess with the random 1 is asy to debug the pop issue
	srand(1);


	// random obstacles
	for (int i = 0; i < 22; ++i) {

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
		m_2dRenderer->setRenderColour(0.4, 00.4, 0);
		for (auto& o : m_navMesh->getObstacles()) {
			m_2dRenderer->drawBox(o.x + o.w * 0.5f, o.y + o.h * 0.5f, o.w, o.h);
		}
	}
}