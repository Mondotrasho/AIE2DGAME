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
	void add_behaviour(Behaviour* behaviour); 

	//agent uodate partitions
	//virtual void sense(float deltaTime);
	//virtual void think(float deltaTime);
	//virtual void act(float deltaTime);
	
	// Update the agent and its behaviours  
	void update(float deltaTime); 

	// Draw the agent  
	virtual void draw(aie::Renderer2D* renderer) = 0; 

	// Movement functions  
	void set_position(Vector2 position) { m_Position = position; }  
	Vector2 get_position() { return m_Position; }  
	void set_velocity(Vector2 velocity) { m_Velocity = velocity; }  
	Vector2 get_velocity() { return m_Velocity; }

protected:

	std::vector<Behaviour*> m_BehaviourList;

	Vector2 m_Position;
	Vector2 m_Velocity;

};