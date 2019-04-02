#pragma once
class Decision
{
public:
	Decision() = default;
	virtual ~Decision();

	virtual void Decide() = 0;
};

