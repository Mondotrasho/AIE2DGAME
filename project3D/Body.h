#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.inl>

namespace aie {
	class Gizmos;
}
class Body
{
public:
	Body(float a,glm::vec4 b ,glm::vec3 c,float d,float z,Body* e, std::vector<Body*> f, glm::mat4 g);
	~Body();


	float Size;
	glm::vec4 colour;
	glm::vec3 position;
	float rotation_speed;
	float orbital_radius{};
	Body* Parent;
	std::vector<Body*> Satellites;

	glm::mat4 Transformation;


	Body* CreateSystem();

	void draw();

	void update(float time);
};

