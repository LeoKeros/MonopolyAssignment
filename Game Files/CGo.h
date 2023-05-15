#pragma once
#include "CSquare.h"

class CGo :
	public CSquare
{
public:
	CGo(const std::string &name, const ushort &location);
	~CGo();

	void LandOn(t_playerpointer & player);
};

