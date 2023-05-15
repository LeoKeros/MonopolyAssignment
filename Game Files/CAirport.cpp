#include "CAirport.h"

//Initialising values that are constant between airports.
CAirport::CAirport(const std::string &name, const ushort &location) : CSquare(name, location)
{
	mType = ESquareType::STAirport;
	mCost = 200;
	mRent = 10;
	mOwner = nullptr;
	mMortgaged = false;
}


CAirport::~CAirport()
{
}

/*
Airport's version of the LandOn function.
Check if the Airport has an owner. If not, the player buys this Airport, even if they cannot afford it.
If the Airport is owned, compare the ID of the player passed to this function with the owner.
If they are the same player, output that the player owns the space.
If they are different players, the player pays rent to the owner IF this property is not mortgaged.
*/
void CAirport::LandOn(t_playerpointer & player)
{
	//If this property is currently unowned.
	if (!mOwner)
	{
		//If the player that landed on this property has enough money to afford this property, buy it.
		// if (player->GetMoneyTotal() >= mCost) // Disabled
		{
			player->ReduceMoneyTotal(mCost);
			player->AddProperty(this, mCost);
			mOwner = player.get();
		}
	}
	//If the owner of this property is not the player that landed on it, that player must pay rent to the owner.
	else if (mOwner->GetID() != player->GetID())
	{
		if (!mMortgaged)
		{
			player->ReduceMoneyTotal(mRent);
			cout << player->GetID() << PAYMENT_MESSAGE << mRent << AIRPORT_PAYMENT_MESSAGE << endl;
			mOwner->AddMoneyTotal(mRent);
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

//Returns the cost of this airport. Used for comparing costs when inserting into a player's "Owned Properties" list.
ushort CAirport::GetValue()
{
	return mCost;
}

//Returns true if this property has an owner.
bool CAirport::HasOwner()
{
	return (mOwner);
}

//Returns true if this property is mortgaged.
bool CAirport::IsMortgaged()
{
	return mMortgaged;
}

//Gets the id of the owner of this property.
EPlayerPiece CAirport::GetOwner() 
{
	return mOwner->GetID();
}


/*
Mortgage state is tested prior to calling this to ensure the intended result.
*/
void CAirport::ToggleMortgage()
{
	mMortgaged = !mMortgaged;
}