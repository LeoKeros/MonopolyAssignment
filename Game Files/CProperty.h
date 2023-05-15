#pragma once
#include "CSquare.h"


class CProperty :
	public CSquare
{
private:
	static std::vector<CProperty*> mGroupList[8]; //Allows properties to check for ownership.
	ushort mGroup;
	ushort mCost; //How much this property costs to buy.
	ushort mRent; //How much the player that lands on this property has to pay the owner.
	CPlayer* mOwner;
	bool mMortgaged; //If the property has been mortgaged.
public:
	CProperty(const string &name, const ushort &location, const ushort &cost, const ushort &rent, const ushort & group);
	~CProperty();

	void LandOn(t_playerpointer & player); //This is called when the player lands on a space.
	
	bool OwnerOwnsGroup(); //Compares the owner of this property with the owner of properties in the same group.
	EPlayerPiece GetOwner(); //Gets the id of the owner of this property.
	bool HasOwner(); //Returns if the property has an owner.
	
	ushort GetValue(); //Gets the cost of the property.

	bool IsMortgaged(); //Returns if the property is mortgaged.
	void ToggleMortgage(); //Toggles the mortgage state between true and false
};