#include "CSquare.h"

/*
Set the name and location of the space using the paramaters.
This constructor is called as part of the creation of derived objects.
*/
CSquare::CSquare(const std::string &name, const ushort &location)
{
	mName = name;
	mLocation = location;
}


CSquare::~CSquare()
{
}

//Return the name of the space as a string.
string CSquare::GetName()
{
	return mName;
}

//Return the type of square that this space is.
ESquareType CSquare::GetType()
{
	return mType;
}