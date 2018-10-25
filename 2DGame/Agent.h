#pragma once
#include "GameObject.h"
#include "Vector2.h"

class Agent : public GameObject {
public:
	Agent() = default;
	virtual ~Agent() = default;

	void setPosition(Vector2 pos) { Position = pos; }
	Vector2 getPosition() const { return Position; }
	void translate(Vector2 translation) { Position += translation; }

	Vector2 Position;
	Vector2 Velocity = { 0,0 };
	float Acceleration = 0;
	Vector2 Force = {0,0};

	Vector2 maxVelocity = {100,100};
	Vector2 maxForce = { 100,100 };
	void update(float deltaTime) override;

	void AddForce(float addMe);


	void ClampForce();
	void ClampVelocity();
	static void Clamp(Vector2* clampmeh, const Vector2* bymeh);
};

inline void Agent::update(float deltaTime)
{
		for (auto behaviour : m_behaviours)
	{
		behaviour->update(this, deltaTime);
	}

	auto hey = this->getPosition();

	ClampForce();
	ClampVelocity();
	Position += Velocity + Force * deltaTime;

	this->setPosition(Position);

}

inline void Agent::AddForce(float addMe)
{
	Force += addMe;
}

inline void Agent::ClampForce()
{
	Clamp(&Force, &maxForce);
}
inline void Agent::ClampVelocity()
{
	Clamp(&Velocity,&maxVelocity);
}
inline void Agent::Clamp(Vector2* clampmeh,const Vector2* bymeh)
{
	if (clampmeh->x > bymeh->x)
	{
		clampmeh->x = bymeh->x;
	}
	if (clampmeh->y > bymeh->y)
	{
		clampmeh->y = bymeh->y;
	}
}