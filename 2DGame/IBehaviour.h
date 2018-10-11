#ifndef IBEHAVIOUR_H
#define IBEHAVIOUR_H

class GameObject;

enum eBehaviourResult {
	SUCCESS,
	FAILURE,
	RUNNING
};
class IBehaviour {
public:
	// empty constructors and destructors for base class
	IBehaviour() = default;
	virtual ~IBehaviour() = default;
	// pure virtual function for executing theIBehaviour
	virtual eBehaviourResult update(GameObject* gameObject, float deltaTime) = 0;
};
#endif //IBehaviour_H
