#pragma once
#include "CSquare.h"
class CJail :
	public CSquare
{
public:
	CJail(const std::string &name, const ushort &location);
	~CJail();

	void LandOn(t_playerpointer & player);
};

