#pragma once
#include "Decision.h"

class BoolDecision : Decision
{
public:
	BoolDecision() {};
	BoolDecision(Decision* truebranch, Decision* falsebranch):trueBranch(truebranch),falseBranch(falsebranch){}
	~BoolDecision(){};

	void Decide() override;

	bool value;
	Decision* trueBranch;
	Decision* falseBranch;
};

inline void BoolDecision::Decide()
{
	if (value)
		trueBranch->Decide();
	else
		falseBranch->Decide();
}
