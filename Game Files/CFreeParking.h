#pragma once
#include "CSquare.h"

class CFreeParking :
	public CSquare
{
public:
	CFreeParking(const std::string &name, const ushort &location);
	~CFreeParking();

	void LandOn(t_playerpointer & player);
};

