#pragma once
#include "CSquare.h"
class CBonus :
	public CSquare
{
private:
	SLuckEvent mBonuses[6];
public:
	CBonus(const std::string &name, const ushort &location);
	~CBonus();

	void LandOn(t_playerpointer & player);
};

