
#include "CFreeParking.h"


CFreeParking::CFreeParking(const std::string &name, const ushort &location) : CSquare(name, location)
{
	mType = ESquareType::STFreeParking;
}


CFreeParking::~CFreeParking()
{
}

/*
Free Parking's version of the LandOn function.
Outputs a message.
*/
void CFreeParking::LandOn(t_playerpointer & player)
{
	cout << player->GetID() << PARKING_MESSAGE << endl;
}