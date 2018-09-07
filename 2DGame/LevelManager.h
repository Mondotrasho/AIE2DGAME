#pragma once
#include <vector>
#include "Plane.h"
#include "Vector3.h"

namespace aie {
	class Application;
	class Renderer2D;
}

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	//Draw
	void draw_boundries(std::vector<Plane>& planes, aie::Renderer2D * render, aie::Application& app);

	//renderer specifics
	void RandomizeColours(float deltatime);
	float GetRed() { return m_colour.R; }
	float GetGreen() { return m_colour.G; }
	float GetBlue() { return m_colour.B; }

private:
	//vector to store the renderer colour
	Vector3 m_colour;
};

