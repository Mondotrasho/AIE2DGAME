#pragma once
#include "Agent.h"
class VelocityAgent :
	public Agent
{
public:
	VelocityAgent();
	~VelocityAgent() = default;

	void update(float deltatime) override;

	void draw(aie::Renderer2D* renderer) override;

	void SetSize(float size) { dotSize = size; }
	float GetSize() { return dotSize; }

	void SetMaxvelocity(Vector2 newmax) { Maxvelocity = newmax; }
	Vector2 GetMaxvelocity() { return Maxvelocity; }

	void SetMaxforce(Vector2 newmax) { Maxforce = newmax; }
	Vector2 GetMaxforce() { return Maxforce; }

	void add_force(Vector2 force);

protected:
	float dotSize = 1;
	Vector2 velocity;
	Vector2 Maxvelocity = Vector2(10,10);
	Vector2 Maxforce;
};

