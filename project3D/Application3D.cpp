#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../MathsLib/MathsLib/Vector4.h"
#include "../MathsLib/MathsLib/Matrix4.h"
#include "Sphere3D.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos; 

void getFrustumPlanes(const Matrix4& transform, Vector4* planes) {
	// right side
	planes[0] = Vector4(transform[0][3] - transform[0][0],
		transform[1][3] - transform[1][0],
		transform[2][3] - transform[2][0],
		transform[3][3] - transform[3][0]);
	// left side
	planes[1] = Vector4(transform[0][3] + transform[0][0],
		transform[1][3] + transform[1][0],
		transform[2][3] + transform[2][0],
		transform[3][3] + transform[3][0]);
	// top
	planes[2] = Vector4(transform[0][3] - transform[0][1],
		transform[1][3] - transform[1][1],
		transform[2][3] - transform[2][1],
		transform[3][3] - transform[3][1]);
	// bottom
	planes[3] = Vector4(transform[0][3] + transform[0][1],
		transform[1][3] + transform[1][1],
		transform[2][3] + transform[2][1],
		transform[3][3] + transform[3][1]);
	// far
	planes[4] = Vector4(transform[0][3] - transform[0][2],
		transform[1][3] - transform[1][2],
		transform[2][3] - transform[2][2],
		transform[3][3] - transform[3][2]);
	// near
	planes[5] = Vector4(transform[0][3] + transform[0][2],
		transform[1][3] + transform[1][2],
		transform[2][3] + transform[2][2],
		transform[3][3] + transform[3][2]);
	// plane normalisation, based on length of normal
	for (int i = 0; i < 6; i++) {
		float d = Vector3(planes[i].x, planes[i].y, planes[i].z).magnitude();//glm::length(Vector3(planes[i]));
		planes[i] /= d;
	}
}
Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::startup() {
	
	setBackgroundColour(0, 0.3f, 0.3);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));

	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
										  getWindowWidth() / (float)getWindowHeight(),
										  0.1f, 1000.f);
	Matrix4 projection = Matrix4(
		Vector4(m_projectionMatrix[0].x, m_projectionMatrix[0].y, m_projectionMatrix[0].z, m_projectionMatrix[0].w),
		Vector4(m_projectionMatrix[1].x, m_projectionMatrix[1].y, m_projectionMatrix[1].z, m_projectionMatrix[1].w),
		Vector4(m_projectionMatrix[2].x, m_projectionMatrix[2].y, m_projectionMatrix[2].z, m_projectionMatrix[2].w),
		Vector4(m_projectionMatrix[3].x, m_projectionMatrix[3].y, m_projectionMatrix[3].z, m_projectionMatrix[3].w));

	Vector4 planes[6];
	getFrustumPlanes(projection, planes);

	Sphere3D sphere = Sphere3D(Vector3(0,10,0),1);

	for (int i = 0; i < 6; i++) {
		float d = Vector3(planes[i].x, planes[i].y, planes[i].z).distance(sphere.position);
		planes[i].w;
		if (d < -sphere.radius) {
			printf("Behind, don't render it!\n");
			break;
		}
		else if (d < sphere.radius) {
			printf("Touching, we still need to render it!\n");
		}
		else {
			printf("Front, fully visible so render it!\n");
		}
	}

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
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1,1,1,0.4);
	vec4 black(0, 0, 0, 0.4);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis repositioning it 0.1 above ground
	Gizmos::addTransform(mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0.1f,0,1));

	// demonstrate a few shapes
	mat4 t = glm::rotate(mat4(1), time, glm::normalize(vec3(1, 1, 1)));
	t[3] = vec4(-1, 0, 0, 1);

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
