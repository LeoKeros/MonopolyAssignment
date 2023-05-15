#pragma once
#include "Definitions.h"

#include "Game Files/CPlayer.h"
#include "Game Files/CSquare.h"
#include "Game Files/CAirport.h"
#include "Game Files/CBonus.h"
#include "Game Files/CFreeParking.h"
#include "Game Files/CGo.h"
#include "Game Files/CGoToJail.h"
#include "Game Files/CJail.h"
#include "Game Files/CPenalty.h"
#include "Game Files/CProperty.h"

class CMonopoly
{
private:
	typedef unique_ptr<CSquare> t_spacepointer;
	vector<t_playerpointer> mPlayers;
	vector<t_spacepointer> mBoard;
	ushort mNumRounds;
	const ushort mNumPlayers = 2;

public:
	CMonopoly();
	~CMonopoly();

	void Output(const string &message);
	bool LoadFiles(); //Load the seed and Monopoly text files and use them to set up the game.
	void Play(); //Start the simulation.
};