#pragma once
#include <vector>
#include "Behaviour.h"
#include "Vector2.h"

namespace aie {
	class Renderer2D;
}

class Agent
{
public:
	Agent();
	virtual ~Agent() = default;

	// Add a behaviour to the agent  
	void AddBehaviour(Behaviour* behaviour); 

	//agent uodate partitions
	//virtual void sense(float deltaTime);
	//virtual void think(float deltaTime);
	//virtual void act(float deltaTime);

	// Update the agent and its behaviours  
	void Update(float deltaTime); 

	// Draw the agent  
	virtual void Draw(aie::Renderer2D* renderer) = 0; 

	// Movement functions  
	void SetPosition(Vector2 position) { m_Position = position; }  
	Vector2 GetPosition() { return m_Position; }  
	void SetVelocity(Vector2 velocity) { m_Velocity = velocity; }  
	Vector2 GetVelocity() { return m_Velocity; }

protected:

	std::vector<Behaviour*> m_BehaviourList;

	Vector2 m_Position;
	Vector2 m_Velocity;

};

//test
