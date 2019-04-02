#pragma once
enum eBehaviourResult {
	SUCCESS,
	FAILURE,
	RUNNING
};

class GameObject;

class Behaviour {
public:

	// empty constructors and destructors for base class
	Behaviour() {}
	virtual ~Behaviour() {}

	// pure virtual function for executing the behaviour
	virtual eBehaviourResult execute(GameObject* gameObject, float deltaTime) = 0;
};
