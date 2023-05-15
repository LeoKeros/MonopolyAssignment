
#include "CPenalty.h"

//Instantiation of the different penalties that are available.
CPenalty::CPenalty(const std::string &name, const ushort &location) : CSquare(name, location)
{
	mType = ESquareType::STPenalty;
	mPenalties[0] = { "Pay food bill. Player loses "    + POUND, 20  };
	mPenalties[1] = { "Pay phone bill. Player loses "   + POUND, 50  };
	mPenalties[2] = { "Pay heating bill. Player loses " + POUND, 100 };
	mPenalties[3] = { "Pay vehicle tax. Player loses "  + POUND, 150 };
	mPenalties[4] = { "Pay fuel bill. Player loses "    + POUND, 200 };
	mPenalties[5] = { "Pay windfall tax. Player loses " + POUND, 300 };
}


CPenalty::~CPenalty()
{
}

/*
Penalty's version of the LandOn function.
Uses Random to choose one of the 6 options (Result is reduced by 1 for array access).
Output the result and reduce the player's funds by the specified amount.
*/
void CPenalty::LandOn(t_playerpointer & player)
{
	ushort penalty = Random() - 1;
	cout << mPenalties[penalty].mMessage << mPenalties[penalty].mValue << endl;
	player->ReduceMoneyTotal(mPenalties[penalty].mValue);
}