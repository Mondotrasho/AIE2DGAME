#pragma once

class GameObject;

class Condition
{
public:
	virtual ~Condition() {};
	virtual bool test(GameObject* go) const = 0;
};

