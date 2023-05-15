
#include "CGo.h"


CGo::CGo(const std::string &name, const ushort &location) : CSquare(name, location)
{
	mType = STGo;
}


CGo::~CGo()
{
}


/*
Go's version of LandOn.
Go doesn't do anything extra when landed on. (It doesn't even output a message, as this is handled elsewhere).
*/
void CGo::LandOn(t_playerpointer & player)
{
}