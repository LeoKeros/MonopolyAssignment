
#include "CBonus.h"

//Instantiation of the different bonuses that are available.
CBonus::CBonus(const std::string &name, const ushort &location) : CSquare(name, location)
{
	mType = ESquareType::STBonus;
	mBonuses[0] = { "Find some money. Player gains " + POUND, 20 };
	mBonuses[1] = { "Win competition. Player gains " + POUND, 50 };
	mBonuses[2] = { "Tax rebate. Player gains "      + POUND, 100 };
	mBonuses[3] = { "Win lottery. Player gains "	 + POUND, 150 };
	mBonuses[4] = { "Bequest. Player gains "		 + POUND, 200 };
	mBonuses[5] = { "Birthday. Player gains "		 + POUND, 300 };
}


CBonus::~CBonus()
{
}


/*
Bonus' version of the LandOn function.
Uses Random to choose one of the 6 options (Result is reduced by 1 for array access).
Output the result and award the player the specified amount.
*/
void CBonus::LandOn(t_playerpointer & player)
{
	ushort bonus = Random() - 1;
	cout << mBonuses[bonus].mMessage << mBonuses[bonus].mValue << endl;
	player->AddMoneyTotal(mBonuses[bonus].mValue);
}