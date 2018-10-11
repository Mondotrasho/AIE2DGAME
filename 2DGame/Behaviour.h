#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

class GameObject;

enum eBehaviourResult {
	SUCCESS,
	FAILURE,
	RUNNING
};
class Behaviour {
public:
	// empty constructors and destructors for base class
	Behaviour() = default;
	virtual ~Behaviour() = default;
	// pure virtual function for executing the behaviour
	virtual eBehaviourResult update(GameObject* gameObject, float deltaTime) = 0;
};
#endif // BEHAVIOUR_H
