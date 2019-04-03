#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "NavMesh.h"
#include "GameObject.h"
#include "NewPathBehaviour.h"
#include "FollowBehaviour.h"
#include "MouseGenPathFollowBehaviour.h"
#include "Input.h"
#include "FishShool.h"
#include "ActionIdle.h"
#include "ActionMoveAlongPath.h"
#include "FindMyNode.h"
#include "Sequence.h"
#include "ActionPathToTarget.h"
#include "CheckInRangeOfFood.h"
#include "CheckIfInRangeOfTarget.h"
#include "ActionEatFood.h"
#include "Selector.h"

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
	GameObject* Mouse;

	std::vector<Selector*> OR; //OR

	std::vector<Sequence*> FOODAND; //AND
	std::vector<CheckInRangeOfFood*> foodrangers; //first												
	std::vector<ActionPathToTarget*> findfoodpathers; //second
	std::vector<ActionMoveAlongPath*> followfoodpathers; //third
	std::vector<CheckIfInRangeOfTarget*> amiinfoodrangers; //fourth
	std::vector<ActionEatFood*> eatfooders; //fifth

	//idle and sequence
	std::vector<Sequence*> IDLEAND; //AND
	std::vector<FindMyNode*> nodefinders; //first
	std::vector<ActionIdle*> pathgenerators; //second
	std::vector<ActionMoveAlongPath*> followers; //third
	
	std::vector<MouseGenPathBehaviour*> mousepathgenerators;
};
