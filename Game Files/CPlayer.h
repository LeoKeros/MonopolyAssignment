#pragma once
#include "..\Definitions.h"
#include "CSquareFD.h"
#include "CSquare.h"

class CPlayer
{
private:
	EPlayerPiece mID; //Unique identifier
	short int mMoney; //How much money the player has.
	ushort mLocation; //Which space on the board the player is currently located at.
	ushort mNumMortgagedProperties; //How many of this player's properties are mortgaged.
	vector<CSquare*> mPropertiesOwned; //The properties this player owns, in order of value, from lowest to highest. Not just CProperty.
public:
	CPlayer(const ushort &id);
	~CPlayer();

	EPlayerPiece GetID();

	//Money functions
	void OutputBalance();
	int GetMoneyTotal();
	void AddMoneyTotal(const ushort& value);
	void ReduceMoneyTotal(const ushort & value);
	void Mortgage(); //Mortgage the player's lowest value properties.
	void Unmortgage(); //Unmortgage the player's lowest value property.

	//Movement functions
	ushort GetLocation();
	void SetLocation(const ushort &value);
	void AddProperty(CSquare* property, const ushort &value);
	void RollDice(); //Roll a dice to randomly determine how far to move, then move to the corresponding location.
};

