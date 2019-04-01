#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "NavMesh.h"
#include "GameObject.h"
#include "NewPathBehaviour.h"
#include "FollowBehaviour.h"
#include "MouseGenPathFollowBehaviour.h"

class _2DGameApp : public aie::Application {
public:

	_2DGameApp();
	virtual ~_2DGameApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	NavMesh*			m_navMesh;
	GameObject* Fish;
	GameObject* Mouse;

	NewPathBehaviour* newpath;
	FollowPathBehaviour* follow;
	MouseGenPathBehaviour* mousepath;

};
