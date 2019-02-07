#pragma once
#include "Agent.h"
class DotAgent :
	public Agent
{
public:
	DotAgent();
	~DotAgent() = default;


	void draw(aie::Renderer2D* renderer) override;

	void SetSize(float size) { dotSize = size; }
	float GetSize() { return dotSize; }
protected:
	float dotSize = 1;
};

