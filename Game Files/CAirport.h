#pragma once
#include "CSquare.h"

class CAirport :
	public CSquare
{
private:
	ushort mCost; //How much this property costs to buy.
	ushort mRent; //How much the player that lands on this property has to pay the owner.
	CPlayer* mOwner;
	bool mMortgaged; //If the property has been mortgaged.
public:
	CAirport(const std::string &name, const ushort &location);
	~CAirport();

	void LandOn(t_playerpointer & player);
	
	EPlayerPiece GetOwner(); //Gets the id of the owner of this property.
	bool HasOwner(); //Returns if the property has an owner.
	
	ushort GetValue(); //Gets the cost of the property.
	
	bool IsMortgaged(); //Returns if the property is mortgaged.
	void ToggleMortgage(); //Toggles the mortgage state between true and false
};

