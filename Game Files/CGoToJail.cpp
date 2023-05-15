
#include "CGoToJail.h"

//Setting the fine for being sent to jail.
CGoToJail::CGoToJail(const std::string &name, const ushort &location) : CSquare(name, location)
{
	mType = ESquareType::STGoToJail;
	mFine = 50;
}


CGoToJail::~CGoToJail()
{
}

/*
Go To Jail's version of LandOn.
Outputs the arrest messages, fines the player and sends them to the jail space.
*/
void CGoToJail::LandOn(t_playerpointer & player)
{
	cout << player->GetID() << ARREST_MESSAGE << endl;
	cout << player->GetID() << PAYMENT_MESSAGE << mFine << endl;
	player->ReduceMoneyTotal(mFine);
	player->SetLocation(mJailLocation);
}

/*
Set the local "Jail Location" variable using the paramater so that the player is sent to the right space.
*/
void CGoToJail::SetJailLocation(const ushort &loc)
{
	mJailLocation = loc;
}