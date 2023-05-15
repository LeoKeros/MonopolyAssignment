#pragma once
#include "..\Definitions.h"
#include "CSquareFD.h"
#include "CPlayer.h"

class CSquare
{
protected:
	ushort mLocation; //This is the location of the square on the map. Locations are from 0 (Go) to 25 (Purple Street)
	std::string mName;
	ESquareType mType; //This refers to the type of square this represents.

public:
	CSquare(const string &name, const ushort &location);
	virtual ~CSquare();

	string GetName();
	ESquareType GetType();
	virtual void LandOn(t_playerpointer & player) = 0; //This is called when the player lands on a space. Each type of space has it's own LandOn function.
};

