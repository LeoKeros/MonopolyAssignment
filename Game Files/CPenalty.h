#pragma once
#include "CSquare.h"

class CPenalty :
	public CSquare
{
private:
	SLuckEvent mPenalties[6];
public:
	CPenalty(const std::string &name, const ushort &location);
	~CPenalty();

	void LandOn(t_playerpointer & player);
};

