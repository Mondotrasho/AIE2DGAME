#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "NavMesh.h"
#include "GameObject.h"
#include "NewPathBehaviour.h"
#include "FollowBehaviour.h"
#include "MouseGenPathFollowBehaviour.h"
#include "Input.h"

class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();
	void InitializeSchools(int num, bool randspeed);
	void DrawSchools(bool drawschools, bool drawpath, bool drawsmoothpath);

	void InitializeNavMesh();
	virtual bool startup();
	virtual void shutdown();
	void UpdateSchools(float delta_time, aie::Input* input);

	virtual void update(float deltaTime);
	void DrawNavmesh(bool b, bool b1, bool b2);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	NavMesh*			m_navMesh;
	std::vector<GameObject*> Schools;
	GameObject* Mouse;

	std::vector<NewPathBehaviour*> pathgenerators;
	std::vector<FollowPathBehaviour*> followers;
	std::vector<MouseGenPathBehaviour*> mousepathgenerators;

};
