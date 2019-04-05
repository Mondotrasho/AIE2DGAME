#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "NavMesh.h"
#include "GameObject.h"
#include "Input.h"
#include "ActionIdle.h"
#include "ActionMoveAlongPath.h"
#include "FindMyNode.h"
#include "Sequence.h"
#include "ActionPathToTarget.h"
#include "CheckInRangeOfFood.h"
#include "CheckIfInRangeOfTarget.h"
#include "ActionEatFood.h"
#include "Selector.h"
#include "ActionEatFish.h"
#include "CheckInRangeOfEdibleFish.h"
#include "ActionPathToMovingTarget.h"
#include "CheckBeingHunted.h"
#include "ActionPathAwayFromTarget.h"
#include "ActionSwimToTarget.h"

class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();
	void InitializeSchools(int num, bool randspeed);
	void UpdategameObjects(float delta_time, aie::Input* input);
	void DrawgameObjects(bool drawobjects, bool drawpath, bool drawsmoothpath);

	void InitializeNavMesh();
	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	void DrawNavmesh(bool b, bool b1, bool b2);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	NavMesh*			m_navMesh;
	std::vector<GameObject*> Pool;
	float timer = 1;

	//brain "stem"
	std::vector<Selector*> OR; //OR

	//FleeHunters sequence
	std::vector<Sequence*> FLEEAND; //AND
	std::vector<CheckBeingHunted*> huntedcheckers; //first												
	std::vector<ActionPathAwayFromTarget*> pathawayers; //second
	std::vector<ActionMoveAlongPath*> runningpathers; //third

	//fish as food sequence
	std::vector<Sequence*> FISHAND; //AND
	std::vector<CheckInRangeOfEdibleFish*> ediblefishrangers; //first												
	std::vector<ActionPathToMovingTarget*> findfishpathers; //second
	std::vector<ActionMoveAlongPath*> followfishpathers; //third
	std::vector<CheckIfInRangeOfTarget*> amiinfishrangers; //fourth
	std::vector<ActionSwimToTarget*> swimtofish;
	std::vector<ActionEatFish*> eatfishers; //fifth

	//food as food sequence
	std::vector<Sequence*> FOODAND; //AND
	std::vector<CheckInRangeOfFood*> foodrangers; //first												
	std::vector<ActionPathToTarget*> findfoodpathers; //second
	std::vector<ActionMoveAlongPath*> followfoodpathers; //third
	std::vector<CheckIfInRangeOfTarget*> amiinfoodrangers; //fourth
	std::vector<ActionSwimToTarget*> swimtofood;
	std::vector<ActionEatFood*> eatfooders; //fifth

	//idle and sequence
	std::vector<Sequence*> IDLEAND; //AND
	std::vector<FindMyNode*> nodefinders; //first
	std::vector<ActionIdle*> pathgenerators; //second
	std::vector<ActionMoveAlongPath*> followers; //third
};
