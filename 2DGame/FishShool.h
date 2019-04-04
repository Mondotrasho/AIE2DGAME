#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "../dependencies/glfw/include/GLFW/glfw3.h"
#include "Utilities.h"

class FishShool :
	public GameObject
{
public:
	FishShool();
	FishShool(const Vector2& Pos, int Speed, std::vector<GameObject*>* newpool, Node* mynode = nullptr, eTeam myteam = None) : GameObject(Pos, Speed,newpool, mynode, myteam)
	{
		switch (myteam) {
		case Blue: sprite.load("../bin/textures/barrelBlue.png");
			break;
		case Red: sprite.load("../bin/textures/barrelRed.png");
			break;
		case None: sprite.load("../bin/textures/barrelBeige.png");
			break;
		default:;
		}
	}

	~FishShool();

	GameObject fish[8];

	virtual bool isfood() { return false; }
	virtual bool isfish() { return true; }
	virtual bool isschool() { return false; }


	void Draw(aie::Renderer2D* render) override
	{
		switch (team) { 
		case Blue: render->setRenderColour(0, 0, 1);
			break;
		case Red: render->setRenderColour(1, 0,0 );
			break;
		case None: render->setRenderColour(1, 1, 1);
			break;
		default: ; }

		//scale by size
		for (int i = 0; i < size; ++i)
		{
			sprite.scale(1.05, 1.05);
		}
		//rotate to face
		//wiggle using sin width of wiggle * (sin wave * frequency) + the angle I am at
		sprite.setRotate(0.2 * sin(glfwGetTime() * 300 ) + angle);
		sprite.setPosition(position.x, position.y);
		sprite.draw(render);

		//render->drawCircle(position.x, position.y, size);
	}
};

