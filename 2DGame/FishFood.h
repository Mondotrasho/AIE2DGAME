#pragma once
#include "GameObject.h"
class FishFood :
	public GameObject
{
public:
	FishFood() = default;
	FishFood(const Vector2& Pos, int Speed, std::vector<GameObject*>* newpool, Node* mynode = nullptr, eTeam myteam = None) : GameObject(Pos, Speed,newpool, mynode, myteam) {}

	~FishFood() = default;

	virtual bool isfood() { return true; }
	virtual bool isfish() { return false; }
	virtual bool isschool() { return false; }
	void Draw(aie::Renderer2D* render) override
	{
		switch (team) {
		case Blue: render->setRenderColour(0, 0, 1);
			break;
		case Red: render->setRenderColour(1, 0, 0);
			break;
		case None:render->setRenderColour(1, 1, 1);
			break;
		default:;
		}
		render->drawBox(position.x, position.y, size,size);
	}
};

