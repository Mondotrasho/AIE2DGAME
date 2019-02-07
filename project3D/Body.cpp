#include "Body.h"



Body::Body(float a, glm::vec4 b, glm::vec3 c, float d,float z, Body* e, std::vector<Body*> f, glm::mat4 g) : 
Size(a),
colour(b),
position(c),
rotation_speed(d),
Parent(e),
Satellites(f),
Transformation(g),
orbital_radius(z)
{
}

Body::~Body()
{
}

Body* Body::CreateSystem()
{
	Body* Sun = new Body(10.0f, glm::vec4(1.0, 0.5, 0.1, 1), glm::vec3(), 1, 0, nullptr, std::vector<Body*>(),
	                     glm::mat4(1));

	Body* earth = new Body(3.0f, glm::vec4(1.0, 0.5, 0.1, 1), glm::vec3(), 1, 100, nullptr, std::vector<Body*>(),
	                       glm::mat4(1));

	Body* moon = new Body(1.0f, glm::vec4(1.0, 0.5, 0.1, 1), glm::vec3(), 1, 10, nullptr, std::vector<Body*>(),
	                      glm::mat4(1));

	Sun->Satellites.push_back(earth);
	earth->Satellites.push_back(moon);

	return Sun;
}

void Body::draw()
{
	addSphere(glm::vec3(0, 0, 0), Size, 80, 80, colour, &Transformation);
}

void Body::update(float time)
{
	float rotation = time * rotation_speed;

	glm::mat4 orbit_rotation = rotate(glm::mat4(0), rotation, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 body_postion = orbit_rotation * glm::translate(glm::mat4(1), glm::vec3(orbital_radius, 0, 0));

	Transformation = Parent->Transformation * body_postion;

	for (auto sat : Satellites)
		sat->update(time);
}
