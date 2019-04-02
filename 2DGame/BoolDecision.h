#pragma once
#include "Decision.h"

class BoolDecision : Decision
{
public:
	BoolDecision(Decision* truebranch, Decision* falsebranch):trueBranch(truebranch),falseBranch(falsebranch){}
	~BoolDecision();

	void Decide() override
	{
		if (value == true)
			trueBranch->Decide();
		else
			falseBranch->Decide();
	}

	bool value;
	Decision* trueBranch;
	Decision* falseBranch;
};

