
#include "CJail.h"


CJail::CJail(const std::string &name, const ushort &location) : CSquare(name, location)
{
	mType = ESquareType::STJail;
}


CJail::~CJail()
{
}


/*
Jail's version of LandOn.
Is only called when the player lands on this space from a dice roll, not when the player is sent to this space.
Output that the player is only visiting jail.
*/
void CJail::LandOn(t_playerpointer & player)
{
	cout << player->GetID() << VISIT_JAIL_MESSAGE << endl;
}