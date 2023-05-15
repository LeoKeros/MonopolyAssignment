
#include "CPlayer.h"
#include "CProperty.h"
#include "CAirport.h"

/*
Initialise values that are constant between players.
Set the player's ID according to the parameter.
*/
CPlayer::CPlayer(const ushort &id)
{
	mID = static_cast<EPlayerPiece>(id);
	mLocation = 0;
	mMoney = 1500;
	mNumMortgagedProperties = 0;
}

CPlayer::~CPlayer()
{
}

/*
Insert the property into the list by searching linearly for a property that is worth more than the property being added.
Index is set such that when a property that the player owns is found to have a higher value than the new property,
the for loop is exited and the new property is inserted before the higher value property.
*/
void CPlayer::AddProperty(CSquare* property, const ushort &value)
{
	ushort index = mPropertiesOwned.size();
	for(ushort count = 0; count < index; count++)
	{
		switch (mPropertiesOwned[count]->GetType())
		{
		case ESquareType::STProperty:
			if (static_cast<CProperty*>(mPropertiesOwned[count])->GetValue() > value) index = count;
			break;
		case ESquareType::STAirport:
			if (static_cast<CAirport*>(mPropertiesOwned[count])->GetValue() > value) index = count;
			break;
		}
	}

	cout << mID << BUY_MESSAGE[0] << property->GetName() << BUY_MESSAGE[1] << value << endl;

	mPropertiesOwned.insert(mPropertiesOwned.begin() + index, property);
	return;
}

//Return the player's ID.
EPlayerPiece CPlayer::GetID()
{
	return mID;
}

//Output the player's total amount of money to the Command Line.
void CPlayer::OutputBalance()
{
	cout << mID << BALANCE_MESSAGE << mMoney << endl;
}

//Return the player's total amount of money.
int CPlayer::GetMoneyTotal()
{
	return mMoney;
}

//Increase the player's money total by the paramater.
void CPlayer::AddMoneyTotal(const ushort& value)
{
	mMoney += value;
}

/*
Reduce the player's bank value by the parameter. If this results in the player having negative funds,
mortgage properties until their funds are positive.
*/
void CPlayer::ReduceMoneyTotal(const ushort & value)
{
	mMoney -= value;
	if (mMoney < 0)
	{
		Mortgage();
	}
}

/*
Mortgage the lowest value un-mortgaged property.
Mortgage until the player has positive funds.
If there are no more unmortgaged properties remaining, return false.
*/
void CPlayer::Mortgage()
{
	for (ushort count = 0; count < mPropertiesOwned.size(); count++)
	{
		switch (mPropertiesOwned[count]->GetType()) //Cast the property to it's derived type and mortgage (if unmortgaged).
		{
			case ESquareType::STProperty:
			{
				CProperty* tmp = static_cast<CProperty*>(mPropertiesOwned[count]);
				if (!tmp->IsMortgaged())
				{
					mNumMortgagedProperties++;
					mMoney += tmp->GetValue();
					tmp->ToggleMortgage(); //Because the property is not mortgaged, this property will be set to mortgaged.
					cout << tmp->GetName() << MORTGAGE_MESSAGE << endl;
				}
			}
			break;
			case ESquareType::STAirport:
			{
				CAirport* tmp = static_cast<CAirport*>(mPropertiesOwned[count]);
				if (!tmp->IsMortgaged())
				{
					mNumMortgagedProperties++;
					mMoney += tmp->GetValue();
					tmp->ToggleMortgage(); //Because the property is not mortgaged, this property will be set to mortgaged.
					cout << tmp->GetName() << MORTGAGE_MESSAGE << endl;
				}
			}
			break;
		}
		if (mMoney > 0) //The player has mortgaged enough properties to get back to having positive funds.
		{
			return;
		}
	}
	return; //If this return is reached, it means every property has been mortgaged and the player still has negative money.
}

/*
Unmortgage the lowest value mortgaged property.
Unmortgage until they can't afford to unmortgage the lowest value mortgaged property.
*/
void CPlayer::Unmortgage()
{
	if (mNumMortgagedProperties != 0)
	{
		for (ushort count = 0; count < mPropertiesOwned.size(); count++)
		{
			switch (mPropertiesOwned[count]->GetType()) //Cast the property to it's derived type and unmortgage (if mortgaged).
			{
			case ESquareType::STProperty:
			{
				CProperty* tmp = static_cast<CProperty*>(mPropertiesOwned[count]);
				if (tmp->IsMortgaged())
				{
					if (mMoney < tmp->GetValue()) return;
					mNumMortgagedProperties--;
					mMoney -= tmp->GetValue();
					tmp->ToggleMortgage(); //Because the property is mortgaged, this property will be set to unmortgaged.
					cout << tmp->GetName() << UNMORTGAGE_MESSAGE << endl;
				}
			}
			break;
			case ESquareType::STAirport:
			{
				CAirport* tmp = static_cast<CAirport*>(mPropertiesOwned[count]);
				if (tmp->IsMortgaged())
				{
					if (mMoney < tmp->GetValue()) return;
					mNumMortgagedProperties--;
					mMoney -= tmp->GetValue();
					tmp->ToggleMortgage(); //Because the property is mortgaged, this property will be set to unmortgaged.
					cout << tmp->GetName() << UNMORTGAGE_MESSAGE << endl;
				}
			}
			break;
			}
		}
	}
}

//Return the player's current location on the game board.
ushort CPlayer::GetLocation()
{
	return mLocation;
}

/*
Set the player's location to the parameter.
Only used by "Go To Jail" to set the Player's location to the Jail position.
*/
void CPlayer::SetLocation(const ushort &value)
{
	mLocation = value;
}

/*
Roll a dice to randomly determine how far to move, then move to the corresponding location.
If the roll would take the player to or beyond Go, award the player the award for passing go.
*/
void CPlayer::RollDice() 
{
	ushort result = Random();
	cout << mID << ROLL_MESSAGE << result << endl;
	result = (mLocation + result) % 26;
	if (result < mLocation) //If the result is lower than the current location, the player has passed go.
	{
		mMoney += PASS_GO_AWARD;
		cout << mID << PASS_GO_MESSAGE << PASS_GO_AWARD << endl;
	}
	mLocation = result;
}

//Convert the player's ID into a string to output to the stream.
std::ostream& operator<<(std::ostream& os, EPlayerPiece p)
{
	switch (p)
	{
	case PDog: os << "Dog";    break;
	case PCar: os << "Car"; break;
	default: os.setstate(std::ios_base::failbit);
	}
	return os;
}