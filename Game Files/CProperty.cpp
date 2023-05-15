#include "CProperty.h"

//Instantiates the group list with blank vectors.
std::vector<CProperty*> CProperty::mGroupList[8] = { {}, {}, {}, {},
													 {}, {}, {}, {} };

/*
Initialising constant values.
Initialising from paramaters.
Adding this property to the static group list depending on it's group number.
*/
CProperty::CProperty(const string &name, const ushort &location, const ushort &cost, const ushort &rent, const ushort & group) : CSquare(name, location)
{
	mType = STProperty;

	mCost = cost;
	mRent = rent;
	mGroup = group;
	mOwner = nullptr;
	mMortgaged = false;
	mGroupList[mGroup].push_back(this);
}

CProperty::~CProperty()
{
}

/*
Property's version of the LandOn function.
Check if the property has an owner. If not, the player buys this property, even if they cannot afford it.
If the property is owned, compare the ID of the player passed to this function with the owner.
If they are the same player, output that the player owns the space.
If they are different players, the player pays rent to the owner IF this property is not mortgaged. 
If the owner owns all of that group of properties, rent is doubled.
*/
void CProperty::LandOn(t_playerpointer & player)
{
	//If this property is currently unowned.
	if (!mOwner)
	{
		//If the player that landed on this property has enough money to afford this property, buy it.
		//if (player->GetMoneyTotal() >= mCost) //Disabled to make funds go negative more often
		{
			player->ReduceMoneyTotal(mCost);
			player->AddProperty(this, mCost);
			mOwner = player.get();
		}
		return;		
	}
	//If the owner of this property is not the player that landed on it, that player must pay rent to the owner.
	
	if (mOwner->GetID() != player->GetID())
	{
		if (!mMortgaged)
		{
			ushort toPay = (OwnerOwnsGroup() ? mRent * 2 : mRent); //If the owner owns every property in the group, rent is doubled
			player->ReduceMoneyTotal(toPay); //Reduce the player's money according to rent
			cout << player->GetID() << PAYMENT_MESSAGE << toPay << endl;
			mOwner->AddMoneyTotal(toPay); //Increase the owner's money by the amount the player paid
		}
		else
		{
			cout << mName << MORTGAGED_MESSAGE << endl;
		}
	}
	else
	{
		cout << player->GetID() << OWN_PROPERTY_MESSAGE << mName << endl;
	}
}

//Returns the cost of this property. Used for comparing costs when inserting into a player's "Owned Properties" list.
ushort CProperty::GetValue()
{
	return mCost;
}

//Returns true if this property has an owner.
bool CProperty::HasOwner()
{
	return (mOwner);
}

//Returns true if this property is mortgaged.
bool CProperty::IsMortgaged()
{
	return mMortgaged;
}

/*
Returns true if the owner of this property owns all of the other properties in it's group.
If this property is unowned, return false instead of comparing to other properties.
Compare this property to other properties in the group (This is done by comparing the address of the player that owns the property.)
If any of those properties are unowned, return false.
If the properties have different owners, return false.
If all properties have been checked, and the function has not returned, it means all properties in the group have the same owner; Return true.
*/
bool CProperty::OwnerOwnsGroup() //Compares the owner of this property with the owner of properties in the same group.
{
	if (!mOwner) return false;
	for (auto it = mGroupList[mGroup].begin(); it != mGroupList[mGroup].end(); it++)
	{
		if (!(*it)->HasOwner()) return false;
		if (mOwner->GetID() != (*it)->GetOwner())
		{
			return false;
		}
	}
	return true;
}

//Gets the id of the owner of this property.
EPlayerPiece CProperty::GetOwner() 
{
	return mOwner->GetID();
}

/*
Mortgage state is tested prior to calling this to ensure the intended result.
*/
void CProperty::ToggleMortgage()
{
	mMortgaged = !mMortgaged;
}