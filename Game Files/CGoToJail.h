#pragma once
#include "CSquare.h"
class CGoToJail :
	public CSquare
{
private:
	ushort mFine; //How much the player is fined for being arrested.
	ushort mJailLocation;
public:
	CGoToJail(const std::string &name, const ushort &location);
	~CGoToJail();

	void LandOn(t_playerpointer & player);

	void SetJailLocation(const ushort &loc);
};

