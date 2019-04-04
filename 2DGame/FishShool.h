#pragma once
#include "GameObject.h"
class FishShool :
	public GameObject
{
public:
	FishShool();
	FishShool(const Vector2& Pos, int Speed, std::vector<GameObject*>* newpool, Node* mynode = nullptr, eTeam myteam = None) : GameObject(Pos, Speed,newpool, mynode, myteam) {}

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
		
		render->drawCircle(position.x, position.y, size);
	}
};

