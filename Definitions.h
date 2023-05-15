#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Utility/Random.h"
#include "Game Files/CSquareFD.h"

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::vector;
using std::ifstream;

typedef unsigned short int ushort;
typedef unique_ptr<CPlayer> t_playerpointer;

//This enum is used to identify the type of property for the purpose of pointer casting
// (So that derived functions can be called from the base pointer)
enum ESquareType : ushort
{
	STProperty = 1,
	STGo,
	STAirport,
	STBonus,
	STPenalty,
	STJail,
	STGoToJail,
	STFreeParking
};

enum EPlayerPiece : ushort
{
	PDog = 1,
	PCar,
	PNumPieces
};

//This operator converts the Enum for PlayerPiece into a string for the output.
std::ostream& operator<<(std::ostream& os, EPlayerPiece p);

//Used for storing Penalty and Bonus events.
struct SLuckEvent
{
	string mMessage;
	ushort mValue;
};

//The input files.
const string SETUP_FILE = "Monopoly.txt";
const string RANDOM_SEED_FILE = "seed.txt";

//Constant values.
const string POUND = "\x9c"; //The hex code for £.
const ushort PASS_GO_AWARD = 200; //How much to award a player for passing go.

//Messages unrelated to the game itself (EG, error messages, formatting etc)
const string FAILED_TO_LOAD = "Failed to load property file or seed file"; //There was a problem with loading one of the files.
const string ROUND_SPLITTER = "----------\n"; //Makes each round easier to identify.

//Messages about game progress
const string WELCOME_MESSAGE = "Welcome to Monopoly"; //Output at the start of the game.
const string PASS_GO_MESSAGE = " passes GO and collects " + POUND; //When the player moves over, or lands on, GO.
const string VISIT_JAIL_MESSAGE = " is just visiting"; //When the player lands directly on Jail.
const string BALANCE_MESSAGE = " has " + POUND; //When stating how much money a player has.
const string BUY_MESSAGE[2] = { " buys ", " for " + POUND}; //When a player buys a property. Player Name << buys << property name << for £<< cost
const string ARREST_MESSAGE = " goes to Jail"; //When the player lands on the "Go To Jail" space and is sent to jail.
const string PAYMENT_MESSAGE = " pays " + POUND; //When a player pays money.
const string OWN_PROPERTY_MESSAGE = " owns "; //When a player is already in possession of a property they land on.
const string MORTGAGED_MESSAGE = " is mortgaged"; //When you land on an opponent's mortgaged property.
const string MORTGAGE_MESSAGE = " has been mortgaged"; //Message to notify the observer that a property has been mortgaged.
const string UNMORTGAGE_MESSAGE = " has been unmortgaged"; //MEssage to notify the observer that a property has been unmortgaged.
const string BANKRUPT_MESSAGE = " has gone bankrupt."; //A player has lost due going into negative money with no properties to mortgage.
const string AIRPORT_PAYMENT_MESSAGE = " of goods"; //Is appended to the payment message for an owned airport.
const string PARKING_MESSAGE = " is resting"; //When a player lands on free parking.
const string ROLL_MESSAGE = " rolls "; // Part of the message when rolling the dice.
const string LAND_MESSAGE = " lands on "; // Part of the message when landing on a space.
const string WIN_MESSAGE = " has won!"; //Declaring the winner.
const string TIE_MESSAGE[2] = { "A tie was detected between ", " and " };