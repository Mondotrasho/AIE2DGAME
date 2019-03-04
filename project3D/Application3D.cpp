#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Utils.h"
#include "OzGiz.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos; 

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::startup() {
	
	setBackgroundColour(0, 0.3f, 0.3);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);
	OzGiz::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10,10,10), vec3(0), vec3(0, 1, 0));

	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
										  getWindowWidth() / (float)getWindowHeight(),
										  0.1f, 1000.f);
	
	return true;
}

void Application3D::shutdown() {

	Gizmos::destroy();
}

void Application3D::update(float deltaTime) {

	// query time since application started
	float time = getTime();

	// input example
	aie::Input* input = aie::Input::getInstance();


	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(glm::cos(time) * 10, 10 , glm::sin(time) * 10),
							   vec3(0), vec3(0, 1, 0));

	// wipe the gizmos clean for this frame
	OzGiz::clear();
	Gizmos::clear();

	// draw a simple grid with gizmos
	Utils::drawGrid(10,10);
	

	// add a transform so that we can see the axis repositioning it 0.1 above ground
	Gizmos::addTransform(mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0.1f,0,1));

	// demonstrate a few shapes
	mat4 t = glm::rotate(mat4(1), time, glm::normalize(vec3(1, 1, 1)));
	t[3] = vec4(-1, 0, 0, 1);


	Gizmos::addCapsule(vec3(1,1,1), 2, 1, 10, 10, vec4(0.2, 0.4, 0.3, 1),&t);


	 //quit if we press escape

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective in case window resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
										  getWindowWidth() / (float)getWindowHeight(),
										  0.1f, 1000.f);

	// draw 3D gizmos
	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
	// draw 2D gizmos using an orthogonal projection matrix (or screen dimensions)
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}